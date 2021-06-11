#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "definitions.h"
#include "instructions.h"
#include "process_operand2.h"

void data_processing(struct State *state_ptr, struct Instruction *instruction_ptr);
uint32_t apply_operation(
		enum Opcode opcode,
		uint32_t operand1,
		uint32_t operand2, 
		bool *write_result_ptr,
		bool *carry_flag_ptr); 
void update_condition_codes(struct State *state_ptr, uint32_t result, bool carry_flag);

void data_processing(struct State *state_ptr, struct Instruction *instruction_ptr) {
	bool carry_flag;
	bool write_result;

	uint32_t operand1 = state_ptr->registers.array_access[instruction_ptr->rn];
	uint32_t operand2_processed = (instruction_ptr->immediate_operand) ? 
			process_operand2_immediate_value(instruction_ptr->operand2, &carry_flag) : 
			process_operand2_shifted_register(state_ptr, instruction_ptr->operand2, &carry_flag);

	uint32_t result = apply_operation(
			instruction_ptr->opcode, 
			operand1, 
			operand2_processed, 
			&write_result,
			&carry_flag);

	if (instruction_ptr->set_condition_codes) update_condition_codes(state_ptr, result, carry_flag);

	if (write_result) state_ptr->registers.array_access[instruction_ptr->rd] = result;
}

void update_condition_codes(struct State *state_ptr, uint32_t result, bool carry_flag) {
	if ((result & (1 << 31)) != 0) {
		state_ptr->registers.struct_access.CPSR |= (1 << 31);
	} else {
		state_ptr->registers.struct_access.CPSR &= ~(1 << 31);
	}
	if (result == 0) {
		state_ptr->registers.struct_access.CPSR |= (1 << 30);
	} else {
		state_ptr->registers.struct_access.CPSR &= ~(1 << 30);
	}
	if (carry_flag) {
		state_ptr->registers.struct_access.CPSR |= (1 << 29);
	} else {
		state_ptr->registers.struct_access.CPSR &= ~(1 << 29);
	}
}

uint32_t apply_operation(
		enum Opcode opcode, 
		uint32_t operand1, 
		uint32_t operand2, 
		bool *write_result_ptr,
		bool *carry_flag_ptr) {
	switch (opcode) {
		case AND:	       *write_result_ptr = true;  return operand1 & operand2;
		case EXCLUSIVE_OR:     *write_result_ptr = true;  return operand1 ^ operand2;
		case TEST_BITS:	       *write_result_ptr = false; return operand1 & operand2;
		case TEST_EQUALS:      *write_result_ptr = false; return operand1 ^ operand2;
		case OR:	       *write_result_ptr = true;  return operand1 | operand2;
		case MOVE:	       *write_result_ptr = true;  return operand2;
				       
		case SUBTRACT:	       *write_result_ptr = true;  
				       *carry_flag_ptr = operand2 > operand1;
				       return operand1 - operand2;
		case REVERSE_SUBTRACT: *write_result_ptr = true;  
				       *carry_flag_ptr = operand1 > operand2;
				       return operand2 - operand1;
		case ADD:	       *write_result_ptr = true;  
				       *carry_flag_ptr = (operand1 > (0xffffffff - operand2));
				       return operand1 + operand2;
		case COMPARE:	       *write_result_ptr = false; 
				       *carry_flag_ptr = !(operand2 > operand1);
				       return operand1 - operand2;
		default:	       return -1;
	}
}



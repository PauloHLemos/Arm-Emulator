#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "definitions.h"
#include "instructions.h"

void data_processing(struct State *state_ptr, struct Instruction *instruction_ptr);
uint32_t apply_operation(
		enum Opcode opcode,
		uint32_t operand1,
		uint32_t operand2, 
		bool *write_result_ptr,
		bool *carry_flag_ptr); 
uint32_t process_operand2_immediate_value(uint32_t operand2, bool *carry_flag_ptr); 
uint32_t process_operand2_shifted_register(
		struct State *state_ptr, 
		uint32_t operand2, 
		bool *carry_flag_ptr);
uint32_t get_shift_amount(struct State *state_ptr, uint32_t operand2);
uint32_t shift(uint32_t rm, uint32_t shift_code, uint32_t shift_amount, bool *carry_flag_ptr);
uint32_t logical_shift_left(uint32_t n, uint32_t spaces, bool *carry_flag_ptr); 
uint32_t logical_shift_right(uint32_t n, uint32_t spaces, bool *carry_flag_ptr);
uint32_t arithmetic_shift_right(uint32_t n, uint32_t spaces, bool *carry_flag_ptr);
uint32_t rotate_right(uint32_t n, uint32_t spaces, bool *carry_flag_ptr);
void set_condition_codes_function(struct State *state_ptr, uint32_t result, bool carry_flag);

void data_processing(struct State *state_ptr, struct Instruction *instruction_ptr) {
	bool carry_flag;
	bool write_result;

	uint32_t operand1 = state_ptr->registers.array_access[instruction_ptr->rn];
	uint32_t operand2_processed = (instruction_ptr->immediate_operand) ? 
			process_operand2_immediate_value(instruction_ptr->operand2, &carry_flag) : 
			process_operand2_shifted_register(
					state_ptr, 
					instruction_ptr->operand2, 
					&carry_flag);

	uint32_t result = apply_operation(
			instruction_ptr->opcode, 
			operand1, 
			operand2_processed, 
			&write_result,
			&carry_flag);

	if (instruction_ptr->set_condition_codes) 
		set_condition_codes_function(state_ptr, result, carry_flag);

	if (write_result) state_ptr->registers.array_access[instruction_ptr->rd] = result;
}

void set_condition_codes_function(struct State *state_ptr, uint32_t result, bool carry_flag) {
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
				       *carry_flag_ptr = operand2 > operand1;
				       return operand1 - operand2;
		default:	       return -1;
	}
}

uint32_t process_operand2_immediate_value(uint32_t operand2, bool *carry_flag_ptr) {
	// bits 0-7 are an unsigned 8 bit number bits 8-11 are a shift to Imm
	uint32_t immediate    = operand2 & 0xff;
	uint32_t shift_amount = 2 * ((operand2 & 0xf00) >> 8);
	return rotate_right(immediate, shift_amount, carry_flag_ptr);
}

uint32_t process_operand2_shifted_register(
		struct State *state_ptr, 
		uint32_t operand2,
		bool *carry_flag_ptr) {
	uint32_t rm_index	   = operand2 & 0xf;
	uint32_t rm		   = state_ptr->registers.array_access[rm_index];
	uint32_t shift_code	   = (operand2 & 0b1100000) >> 5;
	uint32_t shift_amount	   = get_shift_amount(state_ptr, operand2);
	return shift(rm, shift_code, shift_amount, carry_flag_ptr);
}

uint32_t get_shift_amount(struct State *state_ptr, uint32_t operand2) {
	bool bit_4 = (operand2 & 0b10000) != 0;
	if (bit_4) {
		// Register case, bits 8-11 are the register, we use bottom byte of it
		uint32_t rs_index      = (operand2 & 0xf00) >> 8;
		uint32_t rs	       = state_ptr->registers.array_access[rs_index];
		uint32_t rs_first_byte = (rs & 0xff);
		return rs_first_byte;
	} else {
		// Integer case, bits 7-11 are the shift
		uint32_t immediate_shift = ((operand2 & 0b111110000000) >> 7);
		return immediate_shift;
	}
}

uint32_t shift(uint32_t rm, uint32_t shift_code, uint32_t shift_amount, bool *carry_flag_ptr) {
	switch (shift_code) {
		case 0:  return logical_shift_left(rm, shift_amount, carry_flag_ptr); 
		case 1:  return logical_shift_right(rm, shift_amount, carry_flag_ptr); 
		case 2:  return arithmetic_shift_right(rm, shift_amount, carry_flag_ptr); 
		case 3:  return rotate_right(rm, shift_amount, carry_flag_ptr); 
		default: return -1;
	}
}

uint32_t logical_shift_left(uint32_t n, uint32_t spaces, bool *carry_flag_ptr) {
	uint32_t result = (spaces > 31) ? 0 : n << spaces;
	bool carry = (n & (1 << (32 - spaces))) != 0;
	*carry_flag_ptr = carry;
	return result;	
}

uint32_t logical_shift_right(uint32_t n, uint32_t spaces, bool *carry_flag_ptr) {
	uint32_t result = (spaces > 31) ? 0 : n >> spaces;
	bool carry = (n & (1 << (spaces - 1))) != 0;
	*carry_flag_ptr = carry;
	return result;
}

uint32_t arithmetic_shift_right(uint32_t n, uint32_t spaces, bool *carry_flag_ptr) {
	bool sign_bit = (n & (1 << 31)) != 0;
	uint32_t result;
	bool carry = 0;
	if (spaces == 0) {
		return n;
	}

	carry = (n & (1 << (spaces - 1))) != 0;

	if (sign_bit) {
		result = (spaces > 31) ? 0xffffffff : n >> spaces;
		result = result | (0xffffffff << (32 - spaces));
	} else {
		result = (spaces > 31) ? 0 : (n >> spaces);
	}

	*carry_flag_ptr = carry;

	return result;
}

uint32_t rotate_right(uint32_t n, uint32_t spaces, bool *carry_flag_ptr) {
	uint32_t arithmetic_shifted_right = n >> spaces;
	uint32_t overflow_bits		  = n << (32 - spaces);
	bool carry			  = (n & (1 << (spaces - 1))) != 0;
	uint32_t result			  = (arithmetic_shifted_right | overflow_bits);
	*carry_flag_ptr			  = carry;
	return result;
}

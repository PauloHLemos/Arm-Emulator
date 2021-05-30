#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "definitions.h"
#include "instructions.h"

void data_processing(struct State *state_ptr,
		enum Opcode opcode,
		bool immediate_operand,
		bool set_condition_codes,
		uint8_t rn,
		uint8_t rd,
		uint32_t operand2);
uint32_t apply_operation(enum Opcode opcode, 
		uint32_t operand1, 
		uint32_t operand2, 
		bool *write_result_ptr); 
uint32_t process_operand2_immediate_value(uint32_t operand2); 
uint32_t process_operand2_shifted_register(struct State *state_ptr, uint32_t operand2);
enum Shift_Type get_shift_type(uint32_t operand2);
uint32_t get_shift_amount(struct State *state_ptr, uint32_t operand2);
uint32_t shift(uint32_t rm, uint32_t shift_code, uint32_t shift_amount);
uint32_t logical_shift_left(uint32_t n, uint32_t spaces); // PLACEHOLDER
uint32_t logical_shift_right(uint32_t n, uint32_t spaces); // PLACEHOLDER
uint32_t arithmetic_shift_right(uint32_t n, uint32_t spaces); // PLACEHOLDER  
uint32_t rotate_right(uint32_t n, uint32_t spaces); 

void print_binary(uint32_t number);

int main(void) {
	struct State state;
	memset(&state, 0, sizeof(struct State));

	struct Instruction instruction;
	instruction.immediate_operand = false; 
	instruction.set_condition_codes = true;
	instruction.rn = 1; // number from 0-12 for register containing first operand
	instruction.rd = 10; // number from 0-12 for destination register

	//			            109876543210
	state.registers.array_access[0] = 0b111111111111;
	state.registers.array_access[1] = 0b000000000000;
	state.registers.array_access[2] = 0b000000000000;
	state.registers.array_access[3] = 0b000000000000;

	//						 109876543210
	state.registers.array_access[instruction.rn] = 0b000011011011;
	instruction.opcode			     = AND;
	//						 109876543210
	instruction.operand2			     = 0b000001110011; 

	data_processing(&state,
			instruction.opcode,
			instruction.immediate_operand,
			instruction.set_condition_codes,
			instruction.rn,
			instruction.rd,
			instruction.operand2);
	return 0;
}

void data_processing(struct State *state_ptr,
		enum Opcode opcode, bool immediate_operand,
		bool set_condition_codes,
		uint8_t rn,
		uint8_t rd,
		uint32_t operand2) {
	// consider overflows, flag setting
	bool write_result;
	uint32_t operand1 = state_ptr->registers.array_access[rn];
	// assert only the bottome 12 bits of operand2 used?

	uint32_t operand2_processed = (immediate_operand) ? 
			process_operand2_immediate_value(operand2) : 
			process_operand2_shifted_register(state_ptr, operand2);

	uint32_t result = apply_operation(opcode, operand1, operand2_processed, &write_result);
	// calculate result by applying a function corresponding to the opcode,
	// applying to operand1 and operand2
	
	if (set_condition_codes) {
		// set the condition codes
	}

	if (write_result) state_ptr->registers.array_access[rd] = result;
}

uint32_t apply_operation(enum Opcode opcode, 
		uint32_t operand1, 
		uint32_t operand2, 
		bool *write_result_ptr) {
	switch (opcode) {
		case AND:	       *write_result_ptr = true;  return operand1 & operand2;
		case EXCLUSIVE_OR:     *write_result_ptr = true;  return operand1 ^ operand2;
		case SUBTRACT:	       *write_result_ptr = true;  return operand1 - operand2;
		case REVERSE_SUBTRACT: *write_result_ptr = true;  return operand2 - operand1;
		case ADD:	       *write_result_ptr = true;  return operand1 + operand2; 
		case TEST_BITS:	       *write_result_ptr = false; return operand1 & operand2;
		case TEST_EQUALS:      *write_result_ptr = false; return operand1 ^ operand2;
		case COMPARE:	       *write_result_ptr = false; return operand1 - operand2;
		case OR:	       *write_result_ptr = true;  return operand1 | operand2;
		case MOVE:	       *write_result_ptr = true;  return operand2;
		default:	       return -1;
	}
}

uint32_t process_operand2_immediate_value(uint32_t operand2) {
	// bits 0-7 are an unsigned 8 bit number bits 8-11 are a shift to Imm
	uint32_t immediate    = operand2 & 0xff;
	uint32_t shift_amount = 2 * ((operand2 & 0xf00) >> 8);
	return rotate_right(immediate, shift_amount);
}

uint32_t process_operand2_shifted_register(struct State *state_ptr, uint32_t operand2) {
	uint32_t rm_index	   = operand2 & 0xf;
	uint32_t rm		   = state_ptr->registers.array_access[rm_index];
	uint32_t shift_code	   = (operand2 & 0b1100000) >> 5;
	uint32_t shift_amount	   = get_shift_amount(state_ptr, operand2);
	return shift(rm, shift_code, shift_amount);
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

uint32_t shift(uint32_t rm, uint32_t shift_code, uint32_t shift_amount) {
	switch (shift_code) {
		case 0:  return logical_shift_left(rm, shift_amount); 
		case 1:  return logical_shift_right(rm, shift_amount); 
		case 2:  return arithmetic_shift_right(rm, shift_amount); 
		case 3:  return rotate_right(rm, shift_amount); 
		default: return -1;
	}
}

uint32_t logical_shift_left(uint32_t n, uint32_t spaces) {
	return n << spaces;	
}

uint32_t logical_shift_right(uint32_t n, uint32_t spaces) {
	return n >> spaces;
}

uint32_t arithmetic_shift_right(uint32_t n, uint32_t spaces) {
	return 0;
}

uint32_t rotate_right(uint32_t n, uint32_t spaces) {
	uint32_t arithmetic_shifted_right = n >> spaces;
	uint32_t overflow_bits		  = n << (32 - spaces);
	return (arithmetic_shifted_right | overflow_bits);
}

void print_binary(uint32_t number) {
	printf("%u =\t\t", number);
	for (uint32_t i = 0, mask = 1 << 31; i < 32; i++, number <<= 1) {
		printf("%i", ((number & mask) == 0) ? 0 : 1);
	}
	printf("\n");
}

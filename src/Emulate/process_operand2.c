#include <stdint.h>
#include <stdbool.h>
#include "definitions.h"
#include "process_operand2.h"

uint32_t process_operand2_immediate_value(uint32_t operand2, bool *carry_flag_ptr) {
	// bits 0-7 are an unsigned 8 bit number bits 8-11 are a shift to Imm
	uint32_t immediate    = operand2 & 0xff;
	uint32_t shift_amount = 2 * ((operand2 & 0xf00) >> 8);
	return rotate_right(immediate, shift_amount, carry_flag_ptr);
}

uint32_t process_operand2_shifted_register(struct State *state_ptr, uint32_t operand2, bool *carry_flag_ptr) {
	uint32_t rm_index	   = operand2 & 0xf;
	uint32_t rm		   = state_ptr->registers.array_access[rm_index];
	uint32_t shift_code	   = (operand2 & 96 /*1100000*/) >> 5;
	uint32_t shift_amount	   = get_shift_amount(state_ptr, operand2);
	return shift(rm, shift_code, shift_amount, carry_flag_ptr);
}

uint32_t get_shift_amount(struct State *state_ptr, uint32_t operand2) {
	bool bit_4 = (operand2 & 16 /*10000*/) != 0;
	if (bit_4) {
		// Register case, bits 8-11 are the register, we use bottom byte of it
		uint32_t rs_index      = (operand2 & 0xf00) >> 8;
		uint32_t rs	       = state_ptr->registers.array_access[rs_index];
		uint32_t rs_first_byte = (rs & 0xff);
		return rs_first_byte;
	} else {
		// Integer case, bits 7-11 are the shift
		//					111110000000
		uint32_t immediate_shift = ((operand2 & 3968) >> 7);
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
	uint64_t large_result = n << spaces;
	uint32_t result	      = (uint32_t) large_result;
	bool carry	      = (large_result >> 32) != 0;

	*carry_flag_ptr = carry;
	return result;	
}

uint32_t logical_shift_right(uint32_t n, uint32_t spaces, bool *carry_flag_ptr) {
	uint64_t large_result = (((uint64_t) n) << 32) >> spaces;
	bool carry	      = ((1 << 31) & large_result) != 0;
	uint32_t result	      = (uint32_t) (large_result >> 32);

	*carry_flag_ptr	      = carry;
	return result;
}

uint32_t arithmetic_shift_right(uint32_t n, uint32_t spaces, bool *carry_flag_ptr) {
	bool sign_bit	      = (n & (1 << 31)) != 0;
	uint64_t large_result = (((uint64_t) n) << 32) >> spaces;
	bool carry	      = ((1 << 31) & large_result) != 0;
	uint32_t result	      = (uint32_t) (large_result >> 32);

	if (sign_bit) result |= (0xffffffff << (32 - spaces));

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

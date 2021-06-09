#include <stdint.h>
#include <stdbool.h>
#include "definitions.h"
#include "shifts.h"

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

uint32_t rotate_left(uint32_t n, uint32_t spaces, bool *carry_flag_ptr) {
	uint64_t large_result		  = n << spaces;
	uint32_t arithmetic_shifted_left  = (uint32_t) large_result;
	uint32_t overflow_bits		  = n >> (32 - spaces);
	bool carry			  = (large_result >> 32) != 0;
	uint32_t result			  = (arithmetic_shifted_left | overflow_bits);

	*carry_flag_ptr			  = carry;
	return result;
}

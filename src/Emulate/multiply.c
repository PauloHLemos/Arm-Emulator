#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "definitions.h"


void multiply(struct State *state_ptr, struct Instruction *instruction_ptr) {
	uint32_t rm = state_ptr->registers.array_access[instruction_ptr->rm];
	uint32_t rs = state_ptr->registers.array_access[instruction_ptr->rs];
	uint64_t result = rm * rs;
	if (instruction_ptr->accumulate) {
		uint32_t rn = state_ptr->registers.array_access[instruction_ptr->rn];
		result += rn;
	}
	uint64_t u32bitmask = 4294967295;
	uint32_t truncated_result = result & u32bitmask;

	// first we get the current state of the C and V flags
	uint32_t updated_CPSR = state_ptr->registers.struct_access.CPSR & 0b00110000000000000000000000000000;
	if (truncated_result == 0) { 
		updated_CPSR += 0b01000000000000000000000000000000; // updating the zero flag
	}
	if (truncated_result >> 31 == 1) { 
		updated_CPSR += 0b10000000000000000000000000000000; // updating the overflow flag
	}
	if (instruction_ptr->set_condition_codes) {
		state_ptr->registers.struct_access.CPSR = updated_CPSR;
	}
	state_ptr->registers.array_access[instruction_ptr->rd] = truncated_result;
}


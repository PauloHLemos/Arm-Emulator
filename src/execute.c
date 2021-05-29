#include <stdio.h>
#include <stdbool.h>
#include "definitions.h"
#include "execute.h"

void print_binary(uint32_t number) {
	for (int i = 0, mask = 1 << 31; i < 32; i++, number <<= 1) 
		printf("%i", ((number & mask) == 0) ? 0 : 1);
	printf("\n");
}

uint32_t get_negative_flag(struct State *state_ptr) {
	uint32_t mask = 1 << 31;
	return !((state_ptr->registers.struct_access.CPSR & mask) == 0);
}

uint32_t get_zero_flag(struct State *state_ptr) {
	uint32_t mask = 1 << 30;
	return !((state_ptr->registers.struct_access.CPSR & mask) == 0);
}

uint32_t get_carry_flag(struct State *state_ptr) {
	uint32_t mask = 1 << 29;
	return !((state_ptr->registers.struct_access.CPSR & mask) == 0);
}

uint32_t get_overflow_flag(struct State *state_ptr) {
	uint32_t mask = 1 << 28;
	return !((state_ptr->registers.struct_access.CPSR & mask) == 0);
}


int main(void) {
	struct Instruction instruction;
	struct State state;

	uint32_t number = 2588011328;
	print_binary(number);
	instruction.cond = EQUAL;
	state.registers.struct_access.CPSR = number;

	printf("%s\n", get_negative_flag(&state) ? "N flag set" : "N flag clear");
	printf("%s\n", get_zero_flag(&state) ? "Z flag set" : "Z flag clear");
	printf("%s\n", get_carry_flag(&state) ? "C flag set" : "C flag clear");
	printf("%s\n\n", get_overflow_flag(&state) ? "V flag set" : "V flag clear");

	printf("%i\n", execute(instruction, &state));

	return 0;
}

bool execute(struct Instruction instruction, struct State *state_ptr) {
	uint32_t N = get_negative_flag(state_ptr);
	uint32_t Z = get_zero_flag(state_ptr);
	uint32_t C = get_carry_flag(state_ptr);
	uint32_t V = get_overflow_flag(state_ptr);

	switch(instruction.cond) {
		case EQUAL:	         if (!(Z)) { return false; } break;
		case NOT_EQUAL:		 if (!(!Z)) { return false; } break;
		case GREATER_OR_EQUAL:	 if (!(N == V)) { return false; } break;
		case LESS_THAN:		 if (!(N != V)) { return false; } break;
		case GREATER_THAN:	 if (!(!Z && (N == V))) { return false; } break;
		case LESS_THAN_OR_EQUAL: if (!(Z || (N != V))) { return false; } break;
		case ALWAYS:		 break;
	}

	return true;
}

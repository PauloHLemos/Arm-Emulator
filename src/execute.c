#include <stdio.h>
#include <stdbool.h>
#include "definitions.h"
#include "execute.h"

void print_binary(uint32_t number) {
	for (int i = 0, mask = 1 << 31; i < 32; i++, number <<= 1) 
		printf("%i", ((number & mask) == 0) ? 0 : 1);
	printf("\n");
}

bool negative_flag_set(struct State *state_ptr) {
	uint32_t mask = 1 << 31;
	return !((state_ptr->registers.struct_access.CPSR & mask) == 0);
}
bool zero_flag_set(struct State *state_ptr) {
	uint32_t mask = 1 << 30;
	return !((state_ptr->registers.struct_access.CPSR & mask) == 0);
}
bool carry_flag_set(struct State *state_ptr) {
	uint32_t mask = 1 << 29;
	return !((state_ptr->registers.struct_access.CPSR & mask) == 0);
}
bool overflow_flag_set(struct State *state_ptr) {
	uint32_t mask = 1 << 28;
	return !((state_ptr->registers.struct_access.CPSR & mask) == 0);
}


int main(void) {
	struct Instruction instruction;
	struct State state;

	uint32_t number = 633948203840;
	print_binary(number);
	state.registers.struct_access.CPSR = number;

	printf("%s\n", negative_flag_set(&state) ? "Flag set" : "Flag not set");
	printf("%s\n", zero_flag_set(&state) ? "Flag set" : "Flag not set");
	printf("%s\n", carry_flag_set(&state) ? "Flag set" : "Flag not set");
	printf("%s\n", overflow_flag_set(&state) ? "Flag set" : "Flag not set");

	return 0;
}

bool execute(struct Instruction instruction, struct State *state_ptr) {
	if (instruction.cond == EQUAL) {
		printf("%d\n", state_ptr->registers.struct_access.CPSR);

		printf("Equal\n");
	} else if (instruction.cond == NOT_EQUAL) {
		printf("Not equal\n");
	}

	return false;
}

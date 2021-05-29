#include <stdio.h>
#include <stdbool.h>
#include "definitions.h"
#include "execute.h"
#include "instructions.h"

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
	char N = get_negative_flag(state_ptr);
	char Z = get_zero_flag(state_ptr);
	char C = get_carry_flag(state_ptr);
	char V = get_overflow_flag(state_ptr);

	switch(instruction.cond) {
		case EQUAL:	         if (!(Z)) { return false; } break;
		case NOT_EQUAL:		 if (!(!Z)) { return false; } break;
		case GREATER_OR_EQUAL:	 if (!(N == V)) { return false; } break;
		case LESS_THAN:		 if (!(N != V)) { return false; } break;
		case GREATER_THAN:	 if (!(!Z && (N == V))) { return false; } break;
		case LESS_THAN_OR_EQUAL: if (!(Z || (N != V))) { return false; } break;
		case ALWAYS:		 break;
	}

	switch(instruction.type) {
		case DATA_PROCESSING: 
			data_processing(state_ptr,
					instruction.opcode, 
					instruction.immediate_operand,
					instruction.set_condition_codes,
					instruction.rn,
					instruction.rd,
					instruction.operand2);
			break;
		case MULTIPLY: 
			multiply(state_ptr,
					instruction.accumulate,
					instruction.set_condition_codes,
					instruction.rd,
					instruction.rn,
					instruction.rs,
					instruction.rm);
			break;
		case SINGLE_DATA_TRANSFER: 
			single_data_transfer(state_ptr,
					// Might be better to add a bool for immediate offset
					instruction.immediate_operand,
					instruction.pre_post_indexing,
					instruction.up,
					instruction.load_store,
					instruction.rn,
					instruction.rd,
					instruction.offset);
			break;
		case BRANCH: 
			branch(state_ptr, instruction.offset);
			return true;
			break;
	}
	return false;
}

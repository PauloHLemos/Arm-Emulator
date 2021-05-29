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

char get_CPSR_bit(struct State *state_ptr, char bit_no) {
	// indexing starts at 0
	uint32_t mask = 1 << bit_no;
	return !((state_ptr->registers.struct_access.CPSR & mask) == 0);
}

bool condition_met(struct Instruction instruction, struct State *state_ptr) {
	char N = get_CPSR_bit(state_ptr, 31);
	char Z = get_CPSR_bit(state_ptr, 30);
	// char C = get_CPSR_bit(state_ptr, 29); unused
	char V = get_CPSR_bit(state_ptr, 28);

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

bool execute(struct Instruction instruction, struct State *state_ptr) {

	if (!condition_met(instruction, state_ptr)) return false;

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

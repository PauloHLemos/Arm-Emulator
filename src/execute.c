#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "definitions.h"
#include "execute.h"
#include "instructions.h"

char get_CPSR_bit(struct State *state_ptr, char bit_no) {
	// indexing starts at 0
	uint32_t mask = 1 << bit_no;
	return !((state_ptr->registers.struct_access.CPSR & mask) == 0);
}

bool condition_met(struct Instruction *instruction_ptr, struct State *state_ptr) {
	char N = get_CPSR_bit(state_ptr, 31);
	char Z = get_CPSR_bit(state_ptr, 30);
	// char C = get_CPSR_bit(state_ptr, 29); unused
	char V = get_CPSR_bit(state_ptr, 28);

	switch(instruction_ptr->cond) {
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

bool instruction_is_halt(struct Instruction *instruction_ptr) {
	return ((instruction_ptr->cond) == EQUAL) &&
		((instruction_ptr->opcode) == AND) &&
		!(instruction_ptr->immediate_operand) &&
		!(instruction_ptr->set_condition_codes) &&
		((instruction_ptr->rn) == 0) &&
		((instruction_ptr->rd) == 0) &&
		((instruction_ptr->operand2) == 0);
}

bool execute(struct Instruction *instruction_ptr, struct State *state_ptr) {
	if (!instruction_is_halt(instruction_ptr)) {
		instruction_ptr->halt = true;
		return true;
	}

	if (!condition_met(instruction_ptr, state_ptr)) return false;


	switch(instruction_ptr->type) {
		case DATA_PROCESSING: 
			data_processing(state_ptr, instruction_ptr);
			break;
		case MULTIPLY: 
			multiply(state_ptr, instruction_ptr);
			break;
		case SINGLE_DATA_TRANSFER: 
			single_data_transfer(state_ptr, instruction_ptr);
			break;
		case BRANCH: 
			branch(state_ptr, instruction_ptr);
			free(instruction_ptr);
			return true;
			break;
	}
	free(instruction_ptr);
	return false;
}

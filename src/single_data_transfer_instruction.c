#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "definitions.h"

void single_data_transfer(struct State *state_ptr, struct Instruction *instr_ptr);
static uint32_t calculate_offset(struct State state, uint32_t offset);

void single_data_transfer(struct State *state_ptr, struct Instruction *instr_ptr) {
	//struct Instruction instr = *instr_ptr;
	//struct State state = *state_ptr;
	uint32_t offset;
	uint32_t address = state_ptr->registers.array_access[instr_ptr->rn];
	if (instr_ptr->immediate_operand) { //should be immediate_offset
		offset = calculate_offset(*state_ptr, instr_ptr->offset);
	} else {
		offset = instr_ptr->offset; // convert to 12 bit unsigned
	}
	// offset is made negative if its value is to be subtracted instead of added.
	if (!instr_ptr->up) {
		offset = -offset;	
	}
	if (instr_ptr->pre_post_indexing) {
		address += offset;
	}
	// loaded from memory
	assert(address >= 0 && address <=16384); // remove magic number; change to byte addressible addresses.
	if (instr_ptr->load_store) {
		state_ptr->registers.array_access[instr_ptr->rd] = state_ptr->memory[address];
	} // stored to memory
	else {
		state_ptr->memory[address] = state_ptr->registers.array_access[instr_ptr->rd];
	} //do post-indexing if flag set
	if (!instr_ptr->pre_post_indexing) {
		assert(instr_ptr->rn != instr_ptr->rm);
		state_ptr->registers.array_access[instr_ptr->rn] = address + offset;
	}	
}

static uint32_t calculate_offset(struct State state, uint32_t offset) {
	uint8_t base_reg = offset & 15; // get 4 least significant bits
	uint32_t base_val = state.registers.array_access[base_reg];
	// if bit 4 == 0 then shift by constant amount
	if ((offset & 16) == 0) {
		// check shift types and do shift
	} else {
		//optional part will do later
	}
	//dummy return for now
	return 0;
}

int main(int argc, char **argv) {

	struct State state;
	memset(&state, 0, sizeof(struct State));
	
	struct Instruction instr;
	instr.immediate_operand = false;
	instr.up = true;
	instr.pre_post_indexing = true;
	instr.offset = 0;
	instr.rn = 1;
	instr.rd = 2;
	instr.load_store = true;

	state.registers.array_access[1] = 1;
	state.registers.array_access[2] = 2;
	state.memory[0] = 20;
	state.memory[1] = 30;

	single_data_transfer(&state, &instr);	
	printf("%d\n", state.registers.array_access[2]);
	return EXIT_SUCCESS;
}


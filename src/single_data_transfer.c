#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "definitions.h"
#include "process_operand2.h"

void single_data_transfer(struct State *state_ptr, struct Instruction *instr_ptr);
static uint32_t calculate_offset_shifted_register(struct State state, uint32_t offset);

void single_data_transfer(struct State *state_ptr, struct Instruction *instr_ptr) {
	uint32_t offset;
	uint32_t address = state_ptr->registers.array_access[instr_ptr->rn];
	if (instr_ptr->immediate_operand) { //should be immediate_offset
		offset = calculate_offset_shifted_register(*state_ptr, instr_ptr->offset);
	} else {
		offset = instr_ptr->offset; 
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

static uint32_t calculate_offset_shifted_register(struct State state, uint32_t offset) {
	uint8_t base_reg = offset & 15; // get 4 least significant bits
	uint32_t base_val = state.registers.array_access[base_reg];
	bool carry_flag;
	/*
	// if bit 4 == 0 then shift by constant amount
	if ((offset & 16) == 0) {
		// check shift types and do shift
	} else {
		//optional part will do later
	}
	//dummy return for now
	*/
	return process_operand2_shifted_register(&state, offset, &carry_flag);
}

// int main(int argc, char **argv) {
// 
// 	struct State state;
// 	memset(&state, 0, sizeof(struct State));
// 	
// 	struct Instruction instr;
// 	instr.immediate_operand = false;
// 	instr.up = true;
// 	instr.pre_post_indexing = true;
// 	instr.offset = 16;
// 	instr.rn = 1;
// 	instr.rd = 2;
// 	instr.load_store = false;
// 
// 	state.registers.array_access[1] = 4;
// 	state.registers.array_access[2] = 8;
// 	state.memory[0] = 20;
// 	state.memory[4] = 200;
// 	state.memory[20] = 13;
// 
// 	single_data_transfer(&state, &instr);	
// 	printf("%d\n", state.registers.array_access[instr.rd]);
// 	printf("%d\n", state.registers.array_access[instr.rn]);
// 	printf("%d\n", state.memory[20]);
// 	return EXIT_SUCCESS;
// }


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
	// remove magic number; change to byte addressible addresses.
	if (!(address >= 0 && address <= 65533)) {
		printf("Error: Out of bounds memory access at address 0x%08x\n", address);
		return;
	}	
	if (instr_ptr->load_store) {
		state_ptr->registers.array_access[instr_ptr->rd] = 
			(state_ptr->memory[address]) + 
			(state_ptr->memory[address + 1] << 8) +
			(state_ptr->memory[address + 2] << 16) +
			(state_ptr->memory[address + 3] << 24);
	} else { // stored to memory
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

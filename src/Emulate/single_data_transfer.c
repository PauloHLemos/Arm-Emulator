#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "definitions.h"
#include "process_operand2.h"

static uint32_t calculate_offset_shifted_register(struct State state, uint32_t offset) {
	bool carry_flag;
	return process_operand2_shifted_register(&state, offset, &carry_flag);
}

void single_data_transfer(struct State *state_ptr, struct Instruction *instr_ptr) {

	uint32_t address = state_ptr->registers.array_access[instr_ptr->rn];
	uint32_t offset = (instr_ptr->immediate_offset) ? 
			calculate_offset_shifted_register(*state_ptr, instr_ptr->offset) : 
			instr_ptr->offset;

	if (!instr_ptr->up)		  { offset = -offset; }
	if (instr_ptr->pre_post_indexing) { address += offset; } 

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
	} else { 
		uint32_t rd = state_ptr->registers.array_access[instr_ptr->rd];
		state_ptr->memory[address]     = rd;
		state_ptr->memory[address + 1] = rd >> 8;
		state_ptr->memory[address + 2] = rd >> 16;
		state_ptr->memory[address + 3] = rd >> 24;
	} 

	if (!instr_ptr->pre_post_indexing) {
		assert(instr_ptr->rn != instr_ptr->rm);
		state_ptr->registers.array_access[instr_ptr->rn] = address + offset;
	}	
}


 #include <stdint.h>
 #include "definitions.h"

uint32_t fetch(struct State *state_ptr) {
		uint32_t pc = state_ptr->registers.struct_access.PC; 
		uint32_t instruction = 
			(state_ptr->memory[pc+3]<<24) + 
			(state_ptr->memory[pc+2]<<16) + 
			(state_ptr->memory[pc+1]<<8) + 
			state_ptr->memory[pc]; 
		state_ptr->registers.struct_access.PC += 4; return instruction; }

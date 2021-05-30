 #include <stdint.h>
 #include "definitions.h"

uint32_t fetch(State *state) {
		uint32_t pc = state.registers.state_access.PC/4; 
		uint32_t instruction = (state.memory[pc+3]<<24) + (state.memory[pc+2]<<16) + (state.memory[pc+1]<<8) 
			+ state.memory[pc]; 
		state.registers.state_access.PC = state.registers.state_access.PC + 4;
		return instruction;
}

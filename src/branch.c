#include <stdint.h>
#include <stdio.h>
#include "definitions.h"

void branch(struct State *state_ptr, struct Instruction *instruction_ptr){
			uint32_t offset = instruction_ptr->offset;
			//Left shift 2 bits (equivalent to *2^2)
			offset *= 4;
			//Sign extension by 6 bits (equivalent to + 11111100 00000000 00000000 00000000) 
			if (offset >> 25){
					offset += 0b11111100000000000000000000000000;
			state_ptr->registers.struct_access.PC += offset;
			}
}

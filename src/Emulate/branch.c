#include <stdint.h>
#include <stdio.h>
#include "definitions.h"
#include "instructions.h"

void branch(struct State *state_ptr, struct Instruction *instruction_ptr){
	uint32_t offset = instruction_ptr->offset;
	offset <<= 2;
	if ((offset & (1 << 25)) != 0) {
		offset |= 0b11111100000000000000000000000000;
	}
	//Sign extension by 6 bits (equivalent to + 11111100 00000000 00000000 00000000) 

	//TODO: make sure PC is getting the signed effect of the offset
	state_ptr->registers.struct_access.PC += offset;
}

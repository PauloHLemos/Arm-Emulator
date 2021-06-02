#include <stdint.h>
#include <stdio.h>
#include "definitions.h"
#include "instructions.h"

void branch(struct State *state_ptr, struct Instruction *instruction_ptr){
	uint32_t offset = instruction_ptr->offset << 2;
	if ((offset & (1 << 25)) != 0) offset |= 0b11111100000000000000000000000000;
	state_ptr->registers.struct_access.PC += offset;
}

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include "encode.h"
#include "definitions.h"
#include "test_encode.h"

void set_bit(uint32_t *number, char bit_no, bool bit_value) {
	if (bit_value) {
		*number |= (1 << bit_no);
	} else {
		*number &= ~(1 << bit_no);
	}
}

uint32_t encode_data_processing(struct Instruction instruction) {
	uint32_t instruction_binary = 0;
	
	// Flag setting
	set_bit(&instruction_binary, 20, instruction.set_condition_codes); // S bit
	set_bit(&instruction_binary, 25, instruction.immediate_operand);   // I bit

	// Register setting
	assert(instruction.rd < (1 << 4));
	assert(instruction.rn < (1 << 4));
	instruction_binary |= (instruction.rd << 12);
	instruction_binary |= (instruction.rn << 16);

	
	return instruction_binary;
}

uint32_t encode_multiply(struct Instruction instruction) {
	uint32_t instruction_binary = 0;
	
	// Setting default bits
	set_bit(&instruction_binary, 4, 1);
	set_bit(&instruction_binary, 7, 1);
	
	// Flag setting	
	set_bit(&instruction_binary, 20, instruction.set_condition_codes); // S bit
	set_bit(&instruction_binary, 21, instruction.accumulate);	   // A bit
	
	// Register setting
	assert(instruction.rn < (1 << 4));
	assert(instruction.rd < (1 << 4));
	assert(instruction.rs < (1 << 4));
	assert(instruction.rm < (1 << 4));
	instruction_binary |= (instruction.rm);
	instruction_binary |= (instruction.rs << 8);
	instruction_binary |= (instruction.rn << 12);
	instruction_binary |= (instruction.rd << 16);

	return instruction_binary;
}

uint32_t encode_single_data_transfer(struct Instruction instruction) {
	uint32_t instruction_binary = 0;
	// Setting default bits
	set_bit(&instruction_binary, 26, 1);

	// Flag setting
	set_bit(&instruction_binary, 20, instruction.load_store);	 // L bit
	set_bit(&instruction_binary, 23, instruction.up);		 // U bit
	set_bit(&instruction_binary, 24, instruction.pre_post_indexing); // P bit
	set_bit(&instruction_binary, 25, instruction.immediate_offset);  // I bit
	
	// Register setting
	assert(instruction.rd < (1 << 4));
	assert(instruction.rn < (1 << 4));
	instruction_binary |= (instruction.rd << 12);
	instruction_binary |= (instruction.rn << 16);

	return instruction_binary;
}

uint32_t encode_branch(struct Instruction instruction) {
	uint32_t instruction_binary = 0;
	// Setting default bits
	set_bit(&instruction_binary, 25, 1);
	set_bit(&instruction_binary, 27, 1);

	return instruction_binary;
}

uint32_t encode(struct Instruction instruction) {
	switch(instruction.type) {
		case DATA_PROCESSING:	   { return encode_data_processing(instruction); }
		case MULTIPLY:		   { return encode_multiply(instruction); }
		case SINGLE_DATA_TRANSFER: { return encode_single_data_transfer(instruction); }
		case BRANCH:		   { return encode_branch(instruction); }
		default:		   { fprintf(stderr, "Instruction has no opcode. \n"); exit(1); }
	}
}

int main() {
	test_encode();
	return 0;
}

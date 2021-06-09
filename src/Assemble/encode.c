#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include "encode.h"
#include "definitions.h"
#include "test_encode.h"

uint8_t cond_to_int(enum Condition cond) {
	switch(cond) {
		case EQUAL:		 return 0;
		case NOT_EQUAL:		 return 1;
		case GREATER_OR_EQUAL:	 return 10;
		case LESS_THAN:		 return 11;
		case GREATER_THAN:	 return 12;
		case LESS_THAN_OR_EQUAL: return 13;
		case ALWAYS:		 return 14;
	}
}
uint8_t opcode_to_int(enum Opcode opcode) {
	switch(opcode) {
		case AND:	       return 0;
		case EXCLUSIVE_OR:     return 1;
		case SUBTRACT:         return 2;
		case REVERSE_SUBTRACT: return 3;
		case ADD:              return 4;
		case TEST_BITS:        return 8;
		case TEST_EQUALS:      return 9; 
		case COMPARE:	       return 10;
		case OR:               return 12;
		case MOVE:             return 13;
	}                               
}                                       
                                        
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

	// Condition setting
	instruction_binary |= (cond_to_int(instruction.cond) << 28);
	
	// Opcode setting
	instruction_binary |= (opcode_to_int(instruction.opcode) << 21);
	
	// Operand2 setting
	assert(instruction.operand2 < (1 << 12));
	instruction_binary |= instruction.operand2;

	
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
	
	// Condition setting
	instruction_binary |= (cond_to_int(instruction.cond) << 28);

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

	// Condition setting
	instruction_binary |= (cond_to_int(instruction.cond) << 28);

	// Offset setting
	assert(instruction.offset < (1 << 12));
	instruction_binary |= instruction.offset;

	return instruction_binary;
}

uint32_t encode_branch(struct Instruction instruction) {
	uint32_t instruction_binary = 0;
	// Setting default bits
	set_bit(&instruction_binary, 25, 1);
	set_bit(&instruction_binary, 27, 1);

	// Condition setting
	instruction_binary |= (cond_to_int(instruction.cond) << 28);

	// Offset setting
	assert(instruction.offset < (1 << 24));
	instruction_binary |= instruction.offset;

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

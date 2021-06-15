#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include "encode.h"
#include "definitions.h"

uint8_t cond_to_int(enum Condition cond) {
	switch(cond) {
		case EQUAL:		 return 0;
		case NOT_EQUAL:		 return 1;
		case GREATER_OR_EQUAL:	 return 10;
		case LESS_THAN:		 return 11;
		case GREATER_THAN:	 return 12;
		case LESS_THAN_OR_EQUAL: return 13;
		case ALWAYS:		 return 14;
		default:		 { fprintf(stderr, "Instruction has no condition. \n"); exit(1); }
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
		default:	       { fprintf(stderr, "Instruction has no opcode. \n"); exit(1); }
	}                               
}                                       
                                        
void set_bit(uint32_t *number, char bit_index, bool bit_value) {
	assert(0 <= bit_index && bit_index <= 31);
	*number |= (bit_value << bit_index);
}

void set_bits(uint32_t *number, char no_bits, char first_bit_index, uint32_t value) {
	assert(value < (1 << no_bits));
	assert(first_bit_index + no_bits <= 32);
	*number |= (value << first_bit_index);
}

uint32_t encode_data_processing(struct Instruction instruction) {
	uint32_t instruction_binary = 0;
	
	// Flag setting
	set_bit(&instruction_binary, 20, instruction.set_condition_codes); // S bit
	set_bit(&instruction_binary, 25, instruction.immediate_operand);   // I bit

	// Register setting
	set_bits(&instruction_binary, 4, 12, instruction.rd);
	set_bits(&instruction_binary, 4, 16, instruction.rn);

	// Condition setting
	set_bits(&instruction_binary, 4, 28, cond_to_int(instruction.cond));
	
	// Opcode setting
	set_bits(&instruction_binary, 4, 21, opcode_to_int(instruction.opcode));
	
	// Operand2 setting
	set_bits(&instruction_binary, 12, 0, instruction.operand2);
	
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
	set_bits(&instruction_binary, 4, 0, instruction.rm);
	set_bits(&instruction_binary, 4, 8, instruction.rs);
	set_bits(&instruction_binary, 4, 12, instruction.rn);
	set_bits(&instruction_binary, 4, 16, instruction.rd);
	
	// Condition setting
	set_bits(&instruction_binary, 4, 28, cond_to_int(instruction.cond));

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
	set_bits(&instruction_binary, 4, 12, instruction.rd);
	set_bits(&instruction_binary, 4, 16, instruction.rn);

	// Condition setting
	set_bits(&instruction_binary, 4, 28, cond_to_int(instruction.cond));

	// Offset setting
	set_bits(&instruction_binary, 12, 0, instruction.offset);

	return instruction_binary;
}

uint32_t encode_branch(struct Instruction instruction) {
	uint32_t instruction_binary = 0;
	// Setting default bits
	set_bit(&instruction_binary, 25, 1);
	set_bit(&instruction_binary, 27, 1);

	// Condition setting
	set_bits(&instruction_binary, 4, 28, cond_to_int(instruction.cond));

	// Offset setting
	set_bits(&instruction_binary, 24, 0, instruction.offset);

	return instruction_binary;
}

uint32_t encode(struct Instruction instruction) {
	switch(instruction.type) {
		case DATA_PROCESSING:	   { return encode_data_processing(instruction); }
		case MULTIPLY:		   { return encode_multiply(instruction); }
		case SINGLE_DATA_TRANSFER: { return encode_single_data_transfer(instruction); }
		case BRANCH:		   { return encode_branch(instruction); }
		default:		   { fprintf(stderr, "Instruction has no type. \n"); exit(1); }
	}
}


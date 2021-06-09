#include <stdint.h>
#include <stdlib.h>
#include "encode.h"
#include "definitions.h"
#include "test_encode.h"

uint32_t encode_data_processing(struct Instruction instruction) {
	return 0;
}
uint32_t encode_multiply(struct Instruction instruction) {
	return 0;
}
uint32_t encode_single_data_transfer(struct Instruction instruction) {
	return 0;
}
uint32_t encode_branch(struct Instruction instruction) {
	return 0;
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

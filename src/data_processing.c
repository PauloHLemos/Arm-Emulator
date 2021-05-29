#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "definitions.h"
// #include "instructions.h"

void data_processing(struct State *state_ptr,
		enum Opcode opcode,
		bool immediate_operand,
		bool set_condition_codes,
		uint8_t rn,
		uint8_t rd,
		uint32_t operand2) {
	return;
}

int main(void) {
	printf("Hello world\n");
	struct State state;
	struct Instruction instruction;
	memset(&state, 0, sizeof(struct State));

	instruction.opcode = AND;
	instruction.immediate_operand = true; 
	instruction.set_condition_codes = true;
	instruction.rn = 1; // number from 0-12 for register containing first operand
	instruction.rd = 3; // number from 0-12 for destination register
	instruction.operand2 = 15; 


	data_processing(&state,
			instruction.opcode,
			instruction.immediate_operand,
			instruction.set_condition_codes,
			instruction.rn,
			instruction.rd,
			instruction.operand2);

	return 0;
}


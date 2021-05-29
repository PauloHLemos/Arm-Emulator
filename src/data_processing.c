#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "definitions.h"
#include "instructions.h"

void data_processing(struct State *state_ptr,
		enum Opcode opcode,
		bool immediate_operand,
		bool set_condition_codes,
		uint8_t rn,
		uint8_t rd,
		uint32_t operand2) {

	// retrieve operand1 from the register file
	uint32_t operand1 = state_ptr->registers.array_access[rn];

	// calculate operand2
	if (immediate_operand) {
		// process operand2 as immediate value
		
	} else {
		// process operand2 as shifted register

	}

	// calculate result by applying a function corresponding to the opcode,
	// applying to operand1 and operand2
	uint32_t result = 123;
	
	if (set_condition_codes) {
		// set the condition codes
	}

	state_ptr->registers.array_access[rd] = result;
	return;
}

int main(void) {
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

	printf("%d\n", state.registers.array_access[instruction.rd]);

	return 0;
}


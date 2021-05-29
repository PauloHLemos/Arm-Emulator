#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "definitions.h"
#include "instructions.h"

void print_binary(uint16_t number) {
	printf("%d =\t\t", number);
	for (uint16_t i = 0, mask = 1 << 15; i < 16; i++, number <<= 1) {
		printf("%i", ((number & mask) == 0) ? 0 : 1);
	}
	printf("\n");
}
void binary_to_denary(char str[]) {
	int count = 0;
	for (char *str_ptr = str; *str_ptr != '\0'; str_ptr += 1) {
		count += 1;
	}

	int total = 0;
	int counter = 1;
	for (int i = count - 1; i >= 0; i--) {
		char current = *(str + i);
		if (current == '1') { total += counter; }
		counter *= 2;
	}
	printf("%s = %d\n", str, total);
}

void apply_operation(enum Opcode opcode, 
		uint32_t operand1, 
		uint32_t operand2, 
		uint32_t *result, 
		bool *write_result) {
	switch (opcode) {
		// THINK ABOUT OVERFLOWS
		case AND: 
			*result = operand1 & operand2;
			break;
		case EXCLUSIVE_OR: 
			*result = operand1 ^ operand2;
			break;
		case SUBTRACT: 
			*result = operand1 - operand2;
			break;
		case REVERSE_SUBTRACT: 
			*result = operand2 - operand1;
			break;
		case ADD: 
			*result = operand1 + operand2; 
			break;
		case TEST_BITS: 
			*result = operand1 & operand2;
			*write_result = false;
			break;
		case TEST_EQUALS: 
			*result = operand1 ^ operand2;
			*write_result = false;
			break;
		case COMPARE: 
			*result = operand1 - operand2;
			*write_result = false;
			break;
		case OR: 
			*result = operand1 | operand2;
			break;
		case MOVE: 
			*result = operand2;
			break;
	}
}

void data_processing(struct State *state_ptr,
		enum Opcode opcode,
		bool immediate_operand,
		bool set_condition_codes,
		uint8_t rn,
		uint8_t rd,
		uint32_t operand2) {

	// retrieve operand1 from the register file
	uint32_t operand1 = state_ptr->registers.array_access[rn];
	// assert only the bottome 12 bits of operand2 used?

	/*
	// calculate operand2 (temp: as unshifted immediate value)
	if (immediate_operand) {
		// process operand2 as immediate value
		
	} else {
		// process operand2 as shifted register

	}
	*/


	// Split into another function, operand2 processing, consider overflows, flag setting
	uint32_t result = 0;
	bool write_result = true;
	apply_operation(opcode, operand1, operand2, &result, &write_result);

	// calculate result by applying a function corresponding to the opcode,
	// applying to operand1 and operand2
	
	if (set_condition_codes) {
		// set the condition codes
	}

	if (write_result) state_ptr->registers.array_access[rd] = result;
	return;
}

int main(void) {
	struct State state;
	memset(&state, 0, sizeof(struct State));

	struct Instruction instruction;
	instruction.immediate_operand = true; 
	instruction.set_condition_codes = true;
	instruction.rn = 1; // number from 0-12 for register containing first operand
	instruction.rd = 3; // number from 0-12 for destination register
	state.registers.array_access[instruction.rn] = 1234;
	instruction.opcode			     = AND;
	instruction.operand2			     = 10232; 


	print_binary(state.registers.array_access[instruction.rn]);
	print_binary(instruction.operand2);
	printf("------------------------------------------\n");

	data_processing(&state,
			instruction.opcode,
			instruction.immediate_operand,
			instruction.set_condition_codes,
			instruction.rn,
			instruction.rd,
			instruction.operand2);

	print_binary(state.registers.array_access[instruction.rd]);

	return 0;
}


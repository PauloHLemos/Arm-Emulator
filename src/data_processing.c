#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "definitions.h"
#include "instructions.h"

void print_binary(uint32_t number) {
	printf("%u =\t\t", number);
	for (uint32_t i = 0, mask = 1 << 31; i < 32; i++, number <<= 1) {
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
	*write_result = true;
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

void process_operand2_immediate_value(uint32_t *operand2_processed_ptr, uint32_t operand2) {
		// bits 0-7 are an unsigned 8 bit number bits 8-11 are a shift to Imm
		uint32_t immediate		  = operand2 & 0xff; // with implicit zero extension
		uint32_t right_rotation_amount	  = 2 * ((operand2 & 0xf00) >> 8);
		uint32_t arithmetic_shifted_right = immediate >> right_rotation_amount;
		uint32_t overflow_bits		  = immediate << 32 - right_rotation_amount;
		*operand2_processed_ptr		  = arithmetic_shifted_right | overflow_bits;
}

void process_operand2_shifted_register(struct State *state_ptr, 
		uint32_t *operand2_processed_ptr, 
		uint32_t operand2) {

		printf("Operand 2:\t");
		print_binary(operand2);

		uint32_t rm_index = operand2 & 0xf;
		printf("Rm index:\t");
		print_binary(rm_index);

		uint32_t rm = state_ptr->registers.array_access[rm_index];
		printf("Rm:\t\t");
		print_binary(rm);

		uint32_t shift = (operand2 & 0xff0) >> 4;
		printf("Shift:\t\t");
		print_binary(shift);

		// do shift specified by constant amount, maybe do specified by register later
}

void process_operand2(struct State *state_ptr,
		 uint32_t *operand2_processed_ptr, 
		 uint32_t operand2, 
		 bool immediate_operand) {
	if (immediate_operand) {
		process_operand2_immediate_value(operand2_processed_ptr, operand2);
	} else {
		process_operand2_shifted_register(state_ptr, operand2_processed_ptr, operand2);
	}
}



void data_processing(struct State *state_ptr,
		enum Opcode opcode,
		bool immediate_operand,
		bool set_condition_codes,
		uint8_t rn,
		uint8_t rd,
		uint32_t operand2) {
	// consider overflows, flag setting
	bool write_result;
	uint32_t operand2_processed;
	uint32_t operand1 = state_ptr->registers.array_access[rn];
	uint32_t result   = 0;
	// assert only the bottome 12 bits of operand2 used?

	process_operand2(state_ptr, &operand2_processed, operand2, immediate_operand);
	apply_operation(opcode, operand1, operand2, &result, &write_result);

	// calculate result by applying a function corresponding to the opcode,
	// applying to operand1 and operand2
	
	if (set_condition_codes) {
		// set the condition codes
	}

	if (write_result) state_ptr->registers.array_access[rd] = result;
}

int main(void) {
	struct State state;
	memset(&state, 0, sizeof(struct State));

	struct Instruction instruction;
	instruction.immediate_operand = false; 
	instruction.set_condition_codes = true;
	instruction.rn = 1; // number from 0-12 for register containing first operand
	instruction.rd = 3; // number from 0-12 for destination register

	state.registers.array_access[3] = 8754;

	state.registers.array_access[instruction.rn] = 8754;
	instruction.opcode			     = AND;
	instruction.operand2			     = 3267; 


	// print_binary(state.registers.array_access[instruction.rn]);
	// print_binary(instruction.operand2);
	// printf("------------------------------------------\n");

	data_processing(&state,
			instruction.opcode,
			instruction.immediate_operand,
			instruction.set_condition_codes,
			instruction.rn,
			instruction.rd,
			instruction.operand2);

	// print_binary(state.registers.array_access[instruction.rd]);

	return 0;
}


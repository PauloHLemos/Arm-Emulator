#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "definitions.h"
#include "test.h"
#include "split_instructions.h"
#include "test_translate_data_processing.h"
#include "shifts.h"
// #include "instructions.h"

enum Opcode convert_opcode(char *opcode_string) {
	if	(strcmp(opcode_string, "and") == 0) { return AND; } 
	else if (strcmp(opcode_string, "eor") == 0) { return EXCLUSIVE_OR; }
	else if (strcmp(opcode_string, "sub") == 0) { return SUBTRACT; }
	else if (strcmp(opcode_string, "rsb") == 0) { return REVERSE_SUBTRACT; }
	else if (strcmp(opcode_string, "add") == 0) { return ADD; }
	else if (strcmp(opcode_string, "orr") == 0) { return OR; }
	else if (strcmp(opcode_string, "mov") == 0) { return MOVE; }
	else if (strcmp(opcode_string, "tst") == 0) { return TEST_BITS; }
	else if (strcmp(opcode_string, "teq") == 0) { return TEST_EQUALS; }
	else if (strcmp(opcode_string, "cmp") == 0) { return COMPARE; }
	else { fprintf(stderr, "Opcode \"%s\" does not exist. \n", opcode_string); exit(1); return -1; }
}
bool instruction_computes_results(enum Opcode opcode) {
	switch(opcode) {
		case AND:	       return true;
		case EXCLUSIVE_OR:     return true;
		case SUBTRACT:	       return true;
		case REVERSE_SUBTRACT: return true;
		case ADD:	       return true;
		case OR:	       return true;
		default:	       return false;
	}
}

bool instruction_sets_CPSR_only(enum Opcode opcode) {
	switch(opcode) {
		case TEST_BITS:	  return true;
		case TEST_EQUALS: return true;
		case COMPARE:	  return true;
		default:	  return false;
	}
}

uint32_t find_rotation(uint32_t result) {
	assert(result >= (1 << 8));
	uint32_t shifted = result;
	bool carry;
	for (int i = 0; i < 16; i++, shifted = rotate_left(shifted, 2, &carry)) {
		if ((shifted & 0xff) == shifted) {
			return (i << 8) + shifted;
		}
	}
}

void process_operand2(char *operand2_string, uint32_t *operand2_ptr, bool *immediate_operand_ptr) {
	if (*operand2_string == '#') {
		*immediate_operand_ptr = true;
		operand2_string += 1;
		// TODO: fix incomplete behaviour, what if there is an overflow
		uint32_t result = (uint32_t) strtol(operand2_string, NULL, 0); 
		*operand2_ptr = (result >= (1 << 8)) ? find_rotation(result) : result;

	} else {
		*immediate_operand_ptr = false;
		*operand2_ptr = 0;
	}
}


struct Instruction translate_data_processing(char *instruction, struct ST_Node *st_head_ptr) {
	// Make andeq a special case
	
	struct Instruction instruction_struct;
	
	// this won't catch andeq, it will just chop off the eq
	char opcode_string[100];
	extract_opcode(instruction, opcode_string);

	if (strcmp(opcode_string, "andeq") == 0) {
		instruction_struct.opcode = AND;
		instruction_struct.cond	  = EQUAL;
	} else {
		instruction_struct.opcode = convert_opcode(opcode_string);
		instruction_struct.cond   = ALWAYS;
	}

	char operand2_string[100];
	if (instruction_computes_results(instruction_struct.opcode))  {
		// Result computing instructions AND, EOR, SUB, RSB, ADD, ORR
		char rd[100];
		char rn[100];
		split_4_arguments(instruction, opcode_string, rd, rn, operand2_string);

		instruction_struct.rd = *(rd + 1) - '0';
		instruction_struct.rn = *(rn + 1) - '0';
		instruction_struct.set_condition_codes = false;
	} else if (instruction_struct.opcode == MOVE)  {
		// MOV instruction
		char rd[100];
		split_3_arguments(instruction, opcode_string, rd, operand2_string);

		instruction_struct.rd = *(rd + 1) - '0';
		instruction_struct.set_condition_codes = false;
	} else if (instruction_sets_CPSR_only(instruction_struct.opcode)) {
		// CPSR setting instructions
		char rn[100];
		split_3_arguments(instruction, opcode_string, rn, operand2_string);

		instruction_struct.rn = *(rn + 1) - '0';
		instruction_struct.set_condition_codes = true;
	} 
	uint32_t operand2;
	bool immediate_operand;
	process_operand2(operand2_string, &operand2, &immediate_operand);

	instruction_struct.immediate_operand = immediate_operand;
	instruction_struct.operand2	     = operand2;

	return instruction_struct;
}

int main(void) {
	run_tests();
	return 0;
}


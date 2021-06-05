#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "definitions.h"
#include "test.h"
#include "string.h"
#include "split_instructions.h"
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

void process_operand2(char *operand2_string, uint32_t *operand2_ptr, bool *immediate_operand_ptr) {
	printf("%s\n", operand2_string);
}


uint32_t translate_data_processing(char *instruction/*, struct ST_Node *st_head_ptr*/) {
	// Make andeq a special case
	
	struct Instruction instruction_struct;
	
	// this won't catch andeq, it will just chop off the eq
	char opcode_string[100];
	extract_opcode(instruction, opcode_string);

	if (opcode_string == "andeq") {
		instruction_struct.opcode = AND;
		instruction_struct.cond	  = EQUAL;
	} else {
		instruction_struct.opcode = convert_opcode(opcode_string);
		instruction_struct.cond   = ALWAYS;
	}

	char operand2_string[100];
	if (instruction_computes_results(instruction_struct.opcode))  {
		char rd[100];
		char rn[100];
		split_4_arguments(instruction, opcode_string, rd, rn, operand2_string);

		instruction_struct.rd = *(rd + 1) - '0';
		instruction_struct.rn = *(rn + 1) - '0';
		instruction_struct.set_condition_codes = false;
	} else if (instruction_struct.opcode == MOVE)  {
		char rd[100];
		split_3_arguments(instruction, opcode_string, rd, operand2_string);

		instruction_struct.rd = *(rd + 1) - '0';
		instruction_struct.set_condition_codes = false;
	} else if (instruction_sets_CPSR_only(instruction_struct.opcode)) {
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


	return 0;
}

int main(void) {
	translate_data_processing("sub r0, r1, r4, lsl r3");
	return 0;
}


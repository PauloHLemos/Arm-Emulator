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


uint32_t translate_data_processing(char *instruction/*, struct ST_Node *st_head_ptr*/) {
	// Make andeq a special case
	
	struct Instruction instruction_struct;
	
	// this won't catch andeq, it will just chop off the eq
	char instruction_string[30] = "sub r1, r2    , r3, lsl r4";
	char opcode_string[30];
	extract_opcode(instruction_string, opcode_string);

	if (opcode_string == "andeq") {
		instruction_struct.opcode = AND;
		instruction_struct.cond	  = EQUAL;
	} else {
		instruction_struct.opcode = convert_opcode(opcode_string);
		instruction_struct.cond   = ALWAYS;
	}

	char arg1[100];
	char arg2[100];
	char arg3[100];
	char arg4[100];
	split_4_arguments(instruction_string, opcode_string, arg2, arg3, arg4);

	printf("%s\n", opcode_string);
	printf("%s\n", arg2);
	printf("%s\n", arg3);
	printf("%s\n", arg4);



	return 0;
}

int main(void) {
	translate_data_processing("poo r1, r5");
	return 0;
}


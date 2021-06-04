#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "definitions.h"
#include "test.h"
#include "string.h"
// #include "instructions.h"

enum Opcode extract_opcode(char *opcode_string) {
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

void print_at_separators(char *string, char *arg1, char *arg2, char *arg3, char *arg4) {
	for ( ; *string != ' '; string += 1) {
		strncat(arg1, string, 1);
	}
	string += 1;

	for ( ; *string != ','; string += 1) {
		strncat(arg2, string, 1);
	}
	string += (*(string + 1) == ' ') ? 2 : 1;

	for ( ; *string != ','; string += 1) {
		strncat(arg3, string, 1);
	}
	string += (*(string + 1) == ' ') ? 2 : 1;

	for ( ; *string != '\0'; string += 1) {
		strncat(arg4, string, 1);
	}
}

uint32_t translate_data_processing(char *instruction/*, struct ST_Node *st_head_ptr*/) {
	// Make andeq a special case
	
	// struct Instruction instruction_struct;
	
	// this won't catch andeq, it will just chop off the eq
	char opcode_string[30] = "sub r1, r2    , r3, lsl r4";

	char arg1[100] = "";
	char arg2[100] = "";
	char arg3[100] = "";
	char arg4[100] = "";

	print_at_separators(opcode_string, &arg1, &arg2, &arg3, &arg4);

	printf("%s\n", arg1);
	printf("%s\n", arg2);
	printf("%s\n", arg3);
	printf("%s\n", arg4);



	return 0;
}

int main(void) {
	translate_data_processing("poo r1, r5");
	return 0;
}


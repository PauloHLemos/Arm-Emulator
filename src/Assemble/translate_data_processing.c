#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"
#include "test.h"
#include "split_instructions.h"
// #include "instructions.h"
#define EXPECTED_GOT(CONDITION, EXPECTED, GOT, T) \
	do { \
		if (!CONDITION) { \
			printf("\n" #CONDITION ": False \n"); \
			printf("Expected:\t%"T"\n", EXPECTED); \
			printf("Got:\t\t%"T"\n", GOT); \
		} \
	} while (0)

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
	if (*operand2_string == '#') {
		*immediate_operand_ptr = true;
		operand2_string += 1;
		// TODO: fix incomplete behaviour
		*operand2_ptr = atoi(operand2_string); 
	} else {
		*immediate_operand_ptr = false;
	}
}


struct Instruction translate_data_processing(char *instruction/*, struct ST_Node *st_head_ptr*/) {
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

void test_instruction_equals(char *instruction_string,
			     struct Instruction instruction, 
			     char *test_name,
			     enum Condition cond, 
			     bool immediate_operand,
			     enum Opcode opcode,
			     bool set_condition_codes,	
			     uint32_t rn,
			     uint32_t rd,
			     uint32_t operand2) {

	bool cond_correct		 = instruction.cond		   == cond;
	bool immediate_operand_correct	 = instruction.immediate_operand   == immediate_operand;
	bool opcode_correct		 = instruction.opcode		   == opcode;
	bool set_condition_codes_correct = instruction.set_condition_codes == set_condition_codes;
	bool rn_correct			 = instruction.rn		   == rn;
	bool rd_correct 		 = instruction.rd 		   == rd;
	bool operand2_correct		 = instruction.operand2 	   == operand2;

	if (!(cond_correct & immediate_operand_correct & opcode_correct & set_condition_codes_correct
			& rn_correct & rd_correct & operand2_correct)) {
		printf("--------------------------------------\n");
		printf("Test name:\t%s\n"
		       "Instruction:\t%s\n"
		       "Status:\t\tFailed\n", test_name, instruction_string);
	} else {
		printf("--------------------------------------\n");
		printf("Test name:\t%s\n"
		       "Instruction:\t%s\n"
		       "Status:\t\tPassed\n", test_name, instruction_string);
	}

	EXPECTED_GOT(cond_correct,			cond, instruction.cond, "d");
	EXPECTED_GOT(immediate_operand_correct,		immediate_operand, instruction.immediate_operand, "d");
	EXPECTED_GOT(opcode_correct,			opcode, instruction.opcode, "d");
	EXPECTED_GOT(set_condition_codes_correct,	set_condition_codes, instruction.set_condition_codes, "d");
	EXPECTED_GOT(rn_correct,			rn, instruction.rn, "d");
	EXPECTED_GOT(rd_correct,			rd, instruction.rd, "d");
	EXPECTED_GOT(operand2_correct,			operand2, instruction.operand2, "d");
	printf("--------------------------------------\n");
}

void run_tests() {
	char *instruction_string = (char *) malloc(100 * 8 * sizeof(char));
	strncpy(instruction_string, "andeq r0, r0, r0", 100);
	struct Instruction instruction = translate_data_processing(instruction_string);
	test_instruction_equals(instruction_string, instruction, "Andeq halt instruction", 
			EQUAL, // Condition
			false, // Immediate operand 
			AND,   // Opcode 
			0,     // Set condition codes
			0,     // Rn 
			0,     // Rd
			0);    // Operand2


	strncpy(instruction_string, "sub r0, r1, #2342", 100);
	instruction = translate_data_processing(instruction_string);
	test_instruction_equals(instruction_string, instruction, "Sub with immediate operand", 
			ALWAYS, true, SUBTRACT,	0, 1, 0, 2342);		

	strncpy(instruction_string, "add r1, r4, lsl r5", 100);
	instruction = translate_data_processing(instruction_string);
	test_instruction_equals(instruction_string, instruction, "Add with left shift by register",
			ALWAYS, false, ADD, 0, 4, 1, 100);

	free(instruction_string);
}

int main(void) {
	run_tests();
	return 0;
}


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "test_translate_data_processing.h"
#include "definitions.h"
#include "instructions.h"
#define EXPECTED_GOT(CONDITION, EXPECTED, GOT, T) \
	do { \
		if (!CONDITION) { \
			printf("\n" #CONDITION ": False \n"); \
			printf("Expected:\t%"T"\n", EXPECTED); \
			printf("Got:\t\t%"T"\n", GOT); \
		} \
	} while (0)

void test_instruction_equals(char *instruction_string,
			     struct Instruction instruction, 
			     char *test_name,
			     enum Condition cond, bool immediate_operand,
			     enum Opcode opcode,
			     bool set_condition_codes,	
			     uint32_t rd,
			     uint32_t rn,
			     uint32_t operand2) {

	bool instruction_computes_results = (opcode == AND) || 
					    (opcode == EXCLUSIVE_OR) ||
					    (opcode == SUBTRACT) ||
					    (opcode == REVERSE_SUBTRACT) ||
					    (opcode == ADD) ||
					    (opcode == OR);
	bool instruction_is_move	  = (opcode == MOVE);
	bool instruction_sets_cpsr	  = (opcode == TEST_BITS) ||
					    (opcode == TEST_EQUALS) ||
					    (opcode == COMPARE);


	bool cond_correct		 = instruction.cond		   == cond;
	bool immediate_operand_correct	 = instruction.immediate_operand   == immediate_operand;
	bool opcode_correct		 = instruction.opcode		   == opcode;
	bool set_condition_codes_correct = instruction.set_condition_codes == set_condition_codes;
	bool rd_correct 		 = (instruction.rd		   == rd) || instruction_sets_cpsr;
	bool rn_correct			 = (instruction.rn		   == rn) || instruction_is_move;
	bool operand2_correct		 = instruction.operand2		   == operand2;

	bool all_tests_passed = cond_correct &&
				immediate_operand_correct &&
				opcode_correct && 
				set_condition_codes_correct &&
				rn_correct && 
				rd_correct &&
				operand2_correct;

	printf("--------------------------------------------------------------\n"
	       "Test name:\t%s\n"
	       "Instruction:\t%s\n" "Status:\t\t%s\n", 
	       test_name, instruction_string, (all_tests_passed) ? "Passed" : "Failed"); 

	EXPECTED_GOT(cond_correct,		  cond, instruction.cond, "d");
	EXPECTED_GOT(immediate_operand_correct,	  immediate_operand, instruction.immediate_operand, "d");
	EXPECTED_GOT(opcode_correct,		  opcode, instruction.opcode, "d");
	EXPECTED_GOT(set_condition_codes_correct, set_condition_codes, instruction.set_condition_codes, "d");
	EXPECTED_GOT(rd_correct,		  rd, instruction.rd, "d");
	EXPECTED_GOT(rn_correct,		  rn, instruction.rn, "d");
	EXPECTED_GOT(operand2_correct,		  operand2, instruction.operand2, "d");

	printf("--------------------------------------------------------------\n");
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
			0,     // Rd			NULL for TST, TEQ, CMP
			0,     // Rn			NULL for MOV
			0);    // Operand2


	strncpy(instruction_string, "sub r0, r1, #2342", 100); // result 
	instruction = translate_data_processing(instruction_string);
	test_instruction_equals(instruction_string, instruction, "Sub with immediate operand", 
			ALWAYS, true, SUBTRACT,	0, 0, 1, 2342);		

	strncpy(instruction_string, "and r2,r1,#0xAB", 100);
	instruction = translate_data_processing(instruction_string);
	test_instruction_equals(instruction_string, instruction, "Immediate hex operand2", 
			ALWAYS, true, AND, 0, 2, 1, 0b000010101011);		

	strncpy(instruction_string, "mov r3,#0x100", 100);
	instruction = translate_data_processing(instruction_string);
	test_instruction_equals(instruction_string, instruction, "Mov with immediate operand2 with rotation", 
			ALWAYS, true, MOVE, 0, 3, NULL, 0b110000000001);		

	strncpy(instruction_string, "mov r2,#0x3F0000", 100);
	instruction = translate_data_processing(instruction_string);
	test_instruction_equals(instruction_string, instruction, "Mov with immediate operand2 with rotation 2", 
			ALWAYS, true, MOVE, 0, 2, NULL, 0b100000111111);		


	free(instruction_string);
}

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "test_translate_data_processing.h"
#include "definitions.h"
#include "instructions.h"
#define UNUSED 0
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
			     uint32_t operand2,
			     uint32_t *tests_passed,
			     uint32_t *tests_run) {

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
	
	(*tests_run)++;
	if (all_tests_passed) (*tests_passed)++;

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
	uint32_t tests_passed = 0;
	uint32_t tests_run = 0;

	strncpy(instruction_string, "andeq r0, r0, r0", 100);
	struct Instruction instruction = translate_data_processing(instruction_string);
	test_instruction_equals(instruction_string, instruction, "Andeq halt instruction", 
			EQUAL, // Condition
			false, // Immediate operand 
			AND,   // Opcode 
			0,     // Set condition codes	
			0,     // Rd			NULL for TST, TEQ, CMP
			0,     // Rn			NULL for MOV
			0,     // Operand2
			&tests_passed,
			&tests_run);    



	strncpy(instruction_string, "sub r0, r1, #10", 100); // result 
	instruction = translate_data_processing(instruction_string);
	test_instruction_equals(instruction_string, instruction, "Sub with immediate operand", 
			ALWAYS, true, SUBTRACT,	0, 0, 1, 10,
			&tests_passed, &tests_run);		

	strncpy(instruction_string, "sub r0, r1, r4", 100); // result 
	instruction = translate_data_processing(instruction_string);
	test_instruction_equals(instruction_string, instruction, "Sub with register operand", 
			ALWAYS, false, SUBTRACT,	0, 0, 1, 0b000000000100,
			&tests_passed, &tests_run);		

	strncpy(instruction_string, "and r2,r1,#0xAB", 100);
	instruction = translate_data_processing(instruction_string);
	test_instruction_equals(instruction_string, instruction, "Immediate hex operand2", 
			ALWAYS, true, AND, 0, 2, 1, 0b000010101011,
			&tests_passed, &tests_run);		

	strncpy(instruction_string, "mov r3,#0x100", 100);
	instruction = translate_data_processing(instruction_string);
	test_instruction_equals(instruction_string, instruction, "Mov with immediate operand2 with rotation", 
			ALWAYS, true, MOVE, 0, 3, UNUSED, 0b110000000001,
			&tests_passed, &tests_run);		

	strncpy(instruction_string, "mov r2,#0x3F0000", 100);
	instruction = translate_data_processing(instruction_string);
	test_instruction_equals(instruction_string, instruction, "Mov with immediate operand2 with rotation 2", 
			ALWAYS, true, MOVE, 0, 2, UNUSED, 0b100000111111,
			&tests_passed, &tests_run);		

	strncpy(instruction_string, "and r2,r1,#0x3F0000", 100);
	instruction = translate_data_processing(instruction_string);
	test_instruction_equals(instruction_string, instruction, "And with immediate operand2 with rotation", 
			ALWAYS, true, AND, 0, 2, 1, 0b100000111111,
			&tests_passed, &tests_run);		

	strncpy(instruction_string, "sub r5,r4, r3, lsr r2", 100);
	instruction = translate_data_processing(instruction_string);
	test_instruction_equals(instruction_string, instruction, "Sub with operand2 shifted by reg", 
			ALWAYS, false, SUBTRACT, 0, 5, 4, 0b001000110011,
			&tests_passed, &tests_run);		

	strncpy(instruction_string, "sub r5,r4, r3, lsr #24", 100);
	instruction = translate_data_processing(instruction_string);
	test_instruction_equals(instruction_string, instruction, "Sub with operand2 shifted by immediate", 
			ALWAYS, false, SUBTRACT, 0, 5, 4, 0b110000100011,
			&tests_passed, &tests_run);		

	strncpy(instruction_string, "sub r11,r4, r3, lsr #24", 100);
	instruction = translate_data_processing(instruction_string);
	test_instruction_equals(instruction_string, instruction, "Reg number larger than 9", 
			ALWAYS, false, SUBTRACT, 0, 11, 4, 0b110000100011,
			&tests_passed, &tests_run);		


	printf("\n%d of %d tests passed. \n", tests_passed, tests_run);


	free(instruction_string);
}

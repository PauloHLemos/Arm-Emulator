#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "definitions.h"
#include "instructions.h"

void test_instruction(char *instruction_string, struct Instruction instruction, char *test_name,
        enum Condition cond, uint32_t offset, uint32_t *tests_passed, uint32_t *tests_run){

        bool cond_correct = instruction.cond == cond;
        bool offset_correct = instruction.offset == offset;

        bool all_tests_passed = cond_correct && offset_correct;

        (*tests_run)++;
        if (all_tests_passed) (*tests_passed)++;

        printf("--------------------------------------------------------------\n"
        	       "Test name:\t%s\n"
        	       "Instruction:\t%s\n" "Status:\t\t%s\n",
        	       test_name, instruction_string, (all_tests_passed) ? "Passed" : "Failed");
        }


void test_translate_branch(){
	char *instruction_string = (char *) malloc(100 * 8 * sizeof(char));
	uint32_t tests_passed = 0;
	uint32_t tests_run = 0;
    struct Instruction instruction;

    struct ST_Node* head = initialize();
    add_node(head, b, 14);
    add_node(b, beq, 0);
    add_node(beq, bne, 1);
    add_node(bne, bge, 10);
    add_node(bge, blt, 11);
    add_node(blt, bgt, 12);
    add_node(bgt, ble, 13);
    add_node(ble, bal, 14);

	strncpy(instruction_string, "b foo", 100); // result
	instruction = translate_branch(instruction_string, head, 0);
	test_instruction(instruction_string, instruction, "b branch", ALWAYS, 0, &tests_passed, &tests_run);

    strncpy(instruction_string, "beq foo", 100); // result
    instruction = translate_branch(instruction_string, head, 0);
    test_instruction(instruction_string, instruction, "b branch", EQUAL, 0, &tests_passed, &tests_run);

    strncpy(instruction_string, "bne foo", 100); // result
    instruction = translate_branch(instruction_string, head, 0);
    test_instruction(instruction_string, instruction, "b branch", NOT_EQUAL, 0, &tests_passed, &tests_run);

    strncpy(instruction_string, "bge foo", 100); // result
    instruction = translate_branch(instruction_string, head, 0);
    test_instruction(instruction_string, instruction, "b branch", GREATER_OR_EQUAL, 0, &tests_passed, &tests_run);

    strncpy(instruction_string, "blt foo", 100); // result
    instruction = translate_branch(instruction_string, head, 0);
    test_instruction(instruction_string, instruction, "b branch", LESS_THAN, 0, &tests_passed, &tests_run);

    strncpy(instruction_string, "bgt foo", 100); // result
    instruction = translate_branch(instruction_string, head, 0);
    test_instruction(instruction_string, instruction, "b branch", GREATER_THAN, 0, &tests_passed, &tests_run);

    strncpy(instruction_string, "ble foo", 100); // result
    instruction = translate_branch(instruction_string, head, 0);
    test_instruction(instruction_string, instruction, "b branch", LESS_THAN_OR_EQUAL, 0, &tests_passed, &tests_run);

    strncpy(instruction_string, "bal foo", 100); // result
    instruction = translate_branch(instruction_string, head, 0);
    test_instruction(instruction_string, instruction, "b branch", ALWAYS, 0, &tests_passed, &tests_run);

    printf("\n%d of %d tests passed. \n", tests_passed, tests_run);

    free(instruction_string);
}

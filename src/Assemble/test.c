#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "instructions.h"
#include "definitions.h"
#include "convert_instructions.h"

bool assert_true(bool condition, char *error_message) {
	if (!condition) {
		printf("%s\n", error_message);
		return false;
	}
	return true;
}

bool assert_false(bool condition, char *error_message) {
	return assert_true(!condition, error_message);
}

bool assert_int_equals(uint32_t value, uint32_t expected, char *error_message) {
	if (assert_true(value == expected, error_message)) {
		return true;
	} else {
		printf("expected: %d\nrecieved: %d\n", expected, value);
		return false;
	}
}


// example test function
bool test_somefile(void) {
	// run your function in here
	assert_true(1 == 1, "FAIL: somefile.somefunction is not working.");
}

void test_translate_multiply(void) {
	printf("%s\n", "TESTING TRANSLATE MULTIPLY:");

	char *instruction_string_1 = "mul r1, r4, r12";
	struct Instruction instruction_1 = translate_multiply(instruction_string_1);
	assert_int_equals(instruction_1.rd, 1, "mul instruction does not set register rd to correct value");
	assert_int_equals(instruction_1.rm, 4, "mul instruction does not set register rm to correct value");
	assert_int_equals(instruction_1.rs, 12, "mul instruction does not set register rs to correct value");
	assert_false(instruction_1.accumulate, "mul instruction does not set accumulate flag to false");
	assert_false(instruction_1.set_condition_codes, "mul instruction does not set set_condition_codes flag to false");
	assert_int_equals(instruction_1.cond, ALWAYS, "mul instruction does not set condition to ALWAYS");

	char *instruction_string_2 = "mla r6, r10, r12, r2";
	struct Instruction instruction_2 = translate_multiply(instruction_string_2);
	assert_int_equals(instruction_2.rd, 6, "mla instruction does not set register rd to correct value");
	assert_int_equals(instruction_2.rm, 10, "mla instruction does not set register rm to correct value");
	assert_int_equals(instruction_2.rs, 12, "mla instruction does not set register rs to correct value");
	assert_int_equals(instruction_2.rn, 2, "mla instruction does not set register rn to correct value");
	assert_true(instruction_2.accumulate, "mla instruction does not set accumulate flag to true");
	assert_int_equals(instruction_2.cond, ALWAYS, "mla instruction does not set condition to ALWAYS");
	assert_false(instruction_2.set_condition_codes, "mla instruction does not set set_condition_codes flag to false");
}

void test_convert_instructions(void) {
	printf("%s\n", "TESTING CONVERT_INSTRUCTIONS:");

	struct ST_Node *st_head_ptr;

	printf("%s\n", "testing add01 instructions");
	int current_address = 0;
	char *instruction_1 = "mov r1,#1";
	uint32_t binary_1 = 0b11100011101000000001000000000001;
	assert_int_equals(convert_instruction(instruction_1, st_head_ptr, current_address), binary_1, "failed to convert 'add mov r1,#1'");

	current_address += 4;
	char *instruction_2 = "add rn,r1,#2";
	uint32_t binary_2 = 0b11100010100000010010000000000010;
	assert_int_eqauls(convert_instruction(instruction_2, st_head_ptr, current_address), binary_2, "failed to convert 'add rn,r1,#2'");

	printf("%s\n", "testing eor02 instructions");
	int current_address = 0;
	char *instruction_3 = "mov r1,#0xFF";
	uint32_t binary_3 = 0b11100011101000000001000011111111;
	assert_int_equals(convert_instruction(instruction_3, st_head_ptr, current_address), binary_3, "failed to convert 'mov r1,#0xFF'");

	current_address += 4;
	char *instruction_4 = "eor r2,r1,#0x0F";
	uint32_t binary_4 = 0b11100010001000010010000000001111;
	assert_int_equals(convert_instruction(instruction_4, st_head_ptr, current_address), binary_4, "failed to convert 'eor r2,r1,#0x0F'");

	printf("%s\n", "testing loop01 instructions");
	int current_address = 0;
	char *instruction_5 = "mov r2,#0x3F0000";
	uint32_t binary_5 = 0b11100011101000000010100000111111;
	assert_int_equals(convert_instruction(instruction_5, st_head_ptr, current_address), binary_5, "failed to convert 'mov r2,#0x3F0000'");
	
	current_address += 4;
	char *instruction_6 = "sub r2,r2,#1";
	uint32_t binary_6 = 0b11100010010000100010000000000001;
	assert_int_equals(convert_instruction(instruction_6, st_head_ptr, current_address), binary_6, "failed to convert 'sub r2,r2,#1'");

	current_address += 4;
	char *instruction_7 = "cmp r2,#0xFF";
	uint32_t binary_7 = 0b11100011010100100000000011111111;
	assert_int_equals(convert_instruction(instruction_7, st_head_ptr, current_address), binary_7, "failed to convert 'cmp r2,#0xFF'");

	current_address += 4;
	char *instruction_8 = "bne wait";
	uint32_t binary_8 = 0b00011010111111111111111111111100;
	assert_int_equals(convert_instruction(instruction_8, st_head_ptr, current_address), binary_8, "failed to convert 'bne wait'");
}	

int main(void) {
	test_translate_multiply();	
}

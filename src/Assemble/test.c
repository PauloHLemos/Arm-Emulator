#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "instructions.h"
#include "definitions.h"

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
	return assert_true(value == expected, error_message);
}


// example test function
bool test_somefile(void) {
	// run your function in here
	assert_true(1 == 1, "FAIL: somefile.somefunction is not working.");
}

void test_translate_single_data_transfer(void) {
	printf("%s\n", "TESTING SINGLE DATA TRANSFER:"); 

	char *instruction_string_1 = "ldr r0,[r1]";
	struct Instruction instruction_1 = translate_single_data_transfer(instruction_string_1);
	assert_int_equals(instruction_1.rd, 0, "ldr instruction does not set register rd to correct value");
	assert_int_equals(instruction_1.rn, 1, "ldr instruction does not set register rn to correct value");
	assert_int_equals(instruction_1.offset, 0, "ldr instruction does not set offset to correct value");
	//assert_equals(instruction_1.condition, ALWAYS, "mul instruction does not set condition to ALWAYS");
	printf("success test1\n");

	char *instruction_string_2 = "ldr r3,[r1,#8]";
	struct Instruction instruction_2 = translate_single_data_transfer(instruction_string_2);
	assert_int_equals(instruction_2.rd, 3, "ldr instruction does not set register rd to correct value");
	assert_int_equals(instruction_2.rn, 1, "ldr instruction does not set register rn to correct value");
	assert_int_equals(instruction_2.offset, 8, "ldr instruction does not set offset to correct value");
	//assert_equals(instruction_1.condition, ALWAYS, "mul instruction does not set condition to ALWAYS");
	printf("success test2\n");

	char *instruction_string_3 = "ldr r3,[r1,#8]";
	struct Instruction instruction_3 = translate_single_data_transfer(instruction_string_3);
	assert_int_equals(instruction_3.rd, 3, "ldr instruction does not set register rd to correct value");
	assert_int_equals(instruction_3.rn, 1, "ldr instruction does not set register rn to correct value");
	assert_int_equals(instruction_3.offset, 8, "ldr instruction does not set offset to correct value");
	assert_false(instruction_3.immediate_offset, "ldr instruction does not set immediate to correct value");
	assert_int_equals(instruction_3.cond, ALWAYS, "mul instruction does not set condition to ALWAYS");
	printf("success test3\n");

	char *instruction_string_4 = "ldr r10,[r11],#8";
	struct Instruction instruction_4 = translate_single_data_transfer(instruction_string_4);
	assert_int_equals(instruction_4.rd, 10, "ldr instruction does not set register rd to correct value");
	assert_int_equals(instruction_4.rn, 11, "ldr instruction does not set register rn to correct value");
	assert_int_equals(instruction_4.offset, 8, "ldr instruction does not set offset to correct value");
	assert_false(instruction_4.immediate_offset, "ldr instruction does not set immediate to correct value");
	assert_false(instruction_4.pre_post_indexing, "ldr instruction does not set pre_post_index to correct value");
	assert_true(instruction_4.up, "ldr instruction does not set up to correct value");
	assert_int_equals(instruction_4.cond, ALWAYS, "mul instruction does not set condition to ALWAYS");
	printf("success test4\n");

	char *instruction_string_5 = "ldr r10,[r11],#8";
	struct Instruction instruction_5 = translate_single_data_transfer(instruction_string_5);
	assert_int_equals(instruction_5.rd, 10, "ldr instruction does not set register rd to correct value");
	assert_int_equals(instruction_5.rn, 11, "ldr instruction does not set register rn to correct value");
	assert_int_equals(instruction_5.offset, 8, "ldr instruction does not set offset to correct value");
	assert_false(instruction_5.immediate_offset, "ldr instruction does not set immediate to correct value");
	assert_false(instruction_5.pre_post_indexing, "ldr instruction does not set pre_post_index to correct value");
	assert_true(instruction_5.up, "ldr instruction does not set up to correct value");
	assert_int_equals(instruction_5.cond, ALWAYS, "mul instruction does not set condition to ALWAYS");
	printf("success test5\n");

	char *instruction_string_6 = "str r10,[r11],#8";
	struct Instruction instruction_6 = translate_single_data_transfer(instruction_string_6);
	assert_int_equals(instruction_6.rd, 10, "ldr instruction does not set register rd to correct value");
	assert_int_equals(instruction_6.rn, 11, "ldr instruction does not set register rn to correct value");
	assert_int_equals(instruction_6.offset, 8, "ldr instruction does not set offset to correct value");
	assert_false(instruction_6.immediate_offset, "ldr instruction does not set immediate to correct value");
	assert_false(instruction_6.pre_post_indexing, "ldr instruction does not set pre_post_index to correct value");
	assert_true(instruction_6.up, "ldr instruction does not set up to correct value");
	assert_int_equals(instruction_6.cond, ALWAYS, "mul instruction does not set condition to ALWAYS");
	assert_false(instruction_6.load_store, "ldr instruction does not set up to correct value");
	printf("success test6\n");


	char *instruction_string_7 = "str r10,=0x08";
	struct Instruction instruction_7 = translate_single_data_transfer(instruction_string_7);
	assert_int_equals(instruction_7.opcode, 13, "ldr instruction does not set register opcode to correct value");
	/*
	assert_int_equals(instruction_7.rn, 11, "ldr instruction does not set register rn to correct value");
	assert_int_equals(instruction_7.offset, 8, "ldr instruction does not set offset to correct value");
	assert_false(instruction_7.immediate_offset, "ldr instruction does not set immediate to correct value");
	assert_false(instruction_7.pre_post_indexing, "ldr instruction does not set pre_post_index to correct value");
	assert_true(instruction_7.up, "ldr instruction does not set up to correct value");
	assert_int_equals(instruction_7.cond, ALWAYS, "mul instruction does not set condition to ALWAYS");
	assert_false(instruction_7.load_store, "ldr instruction does not set up to correct value");
	*/
	printf("success test7\n");


	/*
	char *instruction_string_2 = "mla r6, r10, r12, r2";
	struct Instruction instruction_2 = translate_multiply(instruction_string_2);
	assert_int_equals(instruction_2.rd, 6, "mla instruction does not set register rd to correct value");
	assert_int_equals(instruction_2.rm, 10, "mla instruction does not set register rm to correct value");
	assert_int_equals(instruction_2.rs, 12, "mla instruction does not set register rs to correct value");
	assert_int_equals(instruction_2.rn, 2, "mla instruction does not set register rn to correct value");
	assert_true(instruction_2.accumulate, "mla instruction does not set accumulate flag to true");
	assert_equals(instruction_2.condition, ALWAYS, "mla instruction does not set condition to ALWAYS");
	assert_false(instruction_2.set_condition_codes, "mla instruction does not set set_condition_codes flag to false");
	*/
}




int main(void) {
	test_translate_single_data_transfer();
}


#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "binary_file_writer.h"
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

// takes in two arrays to compare and returns true if they are equal
bool array_equals(int arr1[], int arr2[], int num_elements) {
	int i;
	for (i = 0; i < num_elements; i++) {
		if (arr1[i] != arr2[i])
			return false;
	}
	return true;
}

// takes two file names and a number of elements and checks that their contents are equal
bool assert_file_equals_file(char *filename1, char *filename2, int num_elements, char *error_message) {
	FILE *file1 = fopen(filename1, "rb");
	FILE *file2 = fopen(filename2, "rb");

	if (file1 == NULL || file2 == NULL) {
		return false;
	}

	uint32_t file1_contents[num_elements];
	size_t file1_size = fread(file1_contents, sizeof(uint32_t), num_elements, file1);

	uint32_t file2_contents[num_elements];
	size_t file2_size = fread(file2_contents, sizeof(uint32_t), num_elements, file2);
	
	if (!array_equals(file1_contents, file2_contents, num_elements)) {
		printf("%s\n", error_message);
		return false;
	}
	return true;
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

}


// unit test suites

void test_binary_file_writer(void) {
	bool all_passed = true;
	
	// put setup here (e.g. creating files for comparison)


	// run your functions in here


	// put your cleanup here (e.g. deleting leftover files used in testing)
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
>>>>>>> src/Assemble/test.c

void test_convert_instructions(void) {
	printf("%s\n", "TESTING CONVERT_INSTRUCTIONS:");

	struct ST_Node *st_head_ptr;

	printf("%s\n", "testing add01 instructions");
	int current_address = 0;
	char *instruction_1 = "mov r1,#1";
	uint32_t binary_1 = 0b11100011101000000001000000000001;
	assert_int_equals(convert_instructions(instruction_1, st_head_ptr, current_address), binary_1, "failed to convert 'add mov r1,#1'");

	current_address += 4;
	char *instruction_2 = "add rn,r1,#2";
	uint32_t binary_2 = 0b11100010100000010010000000000010;
	assert_int_equals(convert_instructions(instruction_2, st_head_ptr, current_address), binary_2, "failed to convert 'add rn,r1,#2'");

	printf("%s\n", "testing eor02 instructions");
	current_address = 0;
	char *instruction_3 = "mov r1,#0xFF";
	uint32_t binary_3 = 0b11100011101000000001000011111111;
	assert_int_equals(convert_instructions(instruction_3, st_head_ptr, current_address), binary_3, "failed to convert 'mov r1,#0xFF'");

	current_address += 4;
	char *instruction_4 = "eor r2,r1,#0x0F";
	uint32_t binary_4 = 0b11100010001000010010000000001111;
	assert_int_equals(convert_instructions(instruction_4, st_head_ptr, current_address), binary_4, "failed to convert 'eor r2,r1,#0x0F'");

	printf("%s\n", "testing loop01 instructions");
	current_address = 0;
	char *instruction_5 = "mov r2,#0x3F0000";
	uint32_t binary_5 = 0b11100011101000000010100000111111;
	assert_int_equals(convert_instructions(instruction_5, st_head_ptr, current_address), binary_5, "failed to convert 'mov r2,#0x3F0000'");
	
	current_address += 4;
	char *instruction_6 = "sub r2,r2,#1";
	uint32_t binary_6 = 0b11100010010000100010000000000001;
	assert_int_equals(convert_instructions(instruction_6, st_head_ptr, current_address), binary_6, "failed to convert 'sub r2,r2,#1'");

	current_address += 4;
	char *instruction_7 = "cmp r2,#0xFF";
	uint32_t binary_7 = 0b11100011010100100000000011111111;
	assert_int_equals(convert_instructions(instruction_7, st_head_ptr, current_address), binary_7, "failed to convert 'cmp r2,#0xFF'");

	current_address += 4;
	char *instruction_8 = "bne wait";
	uint32_t binary_8 = 0b00011010111111111111111111111100;
	assert_int_equals(convert_instructions(instruction_8, st_head_ptr, current_address), binary_8, "failed to convert 'bne wait'");
}	

int main(void) {
	test_translate_single_data_transfer();
	test_binary_file_writer();
	test_translate_multiply();	
	test_convert_instructions();
}


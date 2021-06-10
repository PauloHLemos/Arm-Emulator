#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "translate_multiply.h"
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

bool assert_int_equals(uint32_t value, uint32_t expected, char *error_message) {
	return assert_true(value == expected, error_message);
}


// example test function
bool test_somefile(void) {
	// run your function in here
	assert_true(1 == 1, "FAIL: somefile.somefunction is not working.");
}

bool test_translate_multiply(void) {
	printf("%s\n", "TESTING TRANSLATE MULTIPLY:");

	char *instruction_string_1 = "mul r1, r4, r12";
	struct Instruction instruction_1 = translate_multiply(instruction_string_1);
	assert_int_equals(instruction_1.rd, 1, "mul instruction does not set register rd to correct value");
	assert_int_equals(instruction_1.rm, 4, "mul instruction does not set register rm to correct value");
	assert_int_equals(instruction_1.rs, 12, "mul instruction does not set register rs to correct value");
	assert_false(instruction_1.accumulate, "mul instruction does not set accumulate flag to false");
	assert_false(instruction_1.set_condition_codes, "mul instruction does not set set_condition_codes flag to false");
	assert_equals(instruction_1.condition, ALWAYS, "mul instruction does not set condition to ALWAYS");

	char *instruction_string_2 = "mla r6, r10, r12, r2";
	struct Instruction instruction_2 = translate_multiply(instruction_string_2);
	assert_int_equals(instruction_2.rd, 6, "mla instruction does not set register rd to correct value");
	assert_int_equals(instruction_2.rm, 10, "mla instruction does not set register rm to correct value");
	assert_int_equals(instruction_2.rs, 12, "mla instruction does not set register rs to correct value");
	assert_int_equals(instruction_2.rn, 2, "mla instruction does not set register rn to correct value");
	assert_true(instruction_2.accumulate, "mla instruction does not set accumulate flag to true");
	assert_equals(instruction_2.condition, ALWAYS, "mla instruction does not set condition to ALWAYS");
	assert_false(instruction_2.set_condition_codes, "mla instruction does not set set_condition_codes flag to false");
}

int main(void) {
	test_somefile();
}

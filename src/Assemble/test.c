#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
//#include "somefile.h"

bool assert_true(bool condition, char *error_message) {
	if (!condition) {
		printf("%s\n", error_message);
		return false;
	}
	return true;
}

bool assert_int_equals(uint32_t value, uint32_t expected, char *error_message) {
	if (value != expected) {
		printf("%s\n", error_message);
		return false;
	}
	return true;
}


// example test function
bool test_somefile(void) {
	// run your function in here
	assert_true(1 == 1, "FAIL: somefile.somefunction is not working.");
}


// int main(void) {
// 	test_somefile();
// }

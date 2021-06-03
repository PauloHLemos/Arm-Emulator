#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
//#include "somefile.h"

bool assert_true(bool condition, char *error_message) {
	if (!condition) {
		printf(char);
		return False;
	}
	return True;
}

bool assert_int_equals(uint32_t value, uint32_t expected, char *error_message) {
	if (value != expected) {
		printf(char);
		return False;
	}
	return True;
}


// example test function
bool test_somefile(void) {
	// run your function in here
	assert_true(1 == 1, "FAIL: somefile.somefunction is not working."
}


int main(void) {
	test_somefile();
}

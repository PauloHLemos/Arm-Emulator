#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "binary_file_writer.h"
//#include "somefile.h"

// testing functions

bool assert_true(bool condition, char *error_message) {
	if (!condition) {
		printf(error_message);
		return false;
	}
	return true;
}

bool assert_int_equals(uint32_t value, uint32_t expected, char *error_message) {
	if (value != expected) {
		printf(error_message);
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
	size_t file2_size = freda(file2_contents, sizeof(uint32_t), num_elements, file2);
	
	if (!array_equals(file1_contents, file2_contens, num_elements)) {
		printf(error_message);
		return false;
	}
	return true;
}


// takes in two arrays to compare and returns true if they are equal
bool array_equals(int arr1[], int arr2[], int num_elements) {
	int i;
	for (i = 0; i < size; i++) {
		if (arr1[i] != arr2[i])
			return false;
	}
	return true;
}


// unit test suites

// example test function
bool test_somefile(void) {
	bool all_passed = true;

	// run your function in here
	all_passed = all_passed && assert_true(1 == 1, "FAIL: somefile.somefunction is not working.");

	return all_passed
}

bool test_binary_file_writer(void) {
	bool all_passed = true;
	
	// put setup here (e.g. creating files for comparison)


	// run your functions in here


	// put your cleanup here (e.g. deleting leftover files used in testing)

	return all_passed;
}


int main(void) {
	test_somefile();
	test_binary_file_writer();
}

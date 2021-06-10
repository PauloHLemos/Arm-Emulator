#include <stdlib.h>
#include <stdio.h>
// #include "build_symbol_table.h"
// #include "translate.h"
// #include "symbol_table.h"

int main(int argc, char **argv) {
	if (argc < 3) {
		printf("Not enough arguments. \n");
		return EXIT_FAILURE;
	} else if (argc > 3) {
		printf("Too many arguments. \n");
		return EXIT_FAILURE;
	}

	char *input_filename = *(argv + 1);
	char *output_filename = *(argv + 2);
	
	printf("Input filename: %s\nOutput filename: %s\n", input_filename, output_filename);

	return EXIT_SUCCESS;
}

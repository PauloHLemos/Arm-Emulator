#include <stdlib.h>
#include <stdio.h>
#include "build_symbol_table.h"
#include "translate.h"
#include "symbol_table.h"

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

	FILE *input_file_ptr = fopen(input_filename, "rt");
	if (!input_file_ptr) {
		perror("File could not be opened");
		exit(EXIT_FAILURE);
	}

	struct ST_Node *st_head_ptr = build_symbol_table(input_file_ptr);
	translate(input_file_ptr, st_head_ptr, output_filename);


	fclose(input_file_ptr);
	free(st_head_ptr);
	return EXIT_SUCCESS;
}

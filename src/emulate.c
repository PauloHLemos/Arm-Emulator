#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "definitions.h"
#include "pipeline.h"
#include "loader.h"


void pipeline(struct State *state);

int main(int argc, char **argv) {

	struct State *state_ptr = malloc(sizeof(struct State));
	assert(state_ptr != NULL);
	state_ptr = memset(state_ptr, 0, sizeof(struct State));
	assert(state_ptr != NULL);

	if (argc < 2) {
		printf("Not enough arguments. \n");
		return EXIT_FAILURE;
	} else if (argc > 2) {
		printf("Too many arguments. \n");
		return EXIT_FAILURE;
	}
	char *filename = *(argv + 1);

	loader(filename, state_ptr->memory);

	 pipeline(state_ptr);

	// print the register values here

	free(state_ptr);

	return EXIT_SUCCESS;
}


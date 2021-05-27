#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "definitions.h"
#include "pipeline.h"


void pipeline(struct State *state);

int main(int argc, char **argv) {

	struct State *state_ptr = malloc(sizeof(struct State));
	assert(state_ptr != NULL);
	state_ptr = memset(state_ptr, 0, sizeof(struct State));
	assert(state_ptr != NULL);

	// pipeline(state_ptr);

	return EXIT_SUCCESS;
}


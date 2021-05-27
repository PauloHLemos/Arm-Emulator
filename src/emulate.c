#include <stdlib.h>
#include <stdint.h>
#include "definitions.h"


void pipeline(struct State *state);

int main(int argc, char **argv) {
	struct State state;
	pipeline(&state);
	return EXIT_SUCCESS;
}

void pipeline(struct State *state) {
	return;
}

#include <stdint.h>
#include <stdbool.h>
#include "definitions.h"
#include "pipeline.h"
#include "fetch.h"
#include "decode.h"
#include "execute.h"

void pipeline(struct State *state_ptr) {
	bool ready_to_decode = false;
	bool ready_to_execute = false;
	bool flush = false;
	uint32_t instruction_binary;
	struct Instruction instruction_struct;

	while (!instruction_struct.halt) {
		if (ready_to_execute) {
			flush = execute(&instruction_struct, state_ptr);
			if (flush) {
				ready_to_decode = false;
				ready_to_execute = false;
			}
		}

		if (ready_to_decode) {
			instruction_struct = decode(instruction_binary);
			ready_to_execute = true;
		}

		if (!instruction_struct.halt) {
			instruction_binary = fetch(state_ptr);
		}
		ready_to_decode = true;
	}
}

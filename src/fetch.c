 #include <stdint.h>
 #include "definitions.h"

uint32_t fetch(State *state) {
	return state.memory[(state.registers.PC/4)];
}


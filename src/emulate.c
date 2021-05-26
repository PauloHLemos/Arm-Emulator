#include <stdlib.h>
#include <stdint.h>
#include "definitions.h"



int main(int argc, char **argv) {
	struct State state;
	state.registers.r0 = 5;
	state.registers.R[4] = 10;
	printf("%d\n", state.registers.r0);
	printf("%d\n", state.registers.R[0]);
	printf("%d\n", state.registers.r4);

	state.memory[1230] = 1209; 
	printf("%d\n", state.memory[1230]);

	struct Instruction instruction;
	instruction.opcode = EXCLUSIVE_OR;
	printf("%d\n", instruction.opcode);

	return EXIT_SUCCESS;
}

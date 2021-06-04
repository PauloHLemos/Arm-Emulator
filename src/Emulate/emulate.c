#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "definitions.h"
#include "pipeline.h"
#include "loader.h"

void print_registers(struct State *state_ptr) {
	printf("Registers:\n");
	printf("$0  : %10d (0x%08x)\n", state_ptr->registers.array_access[0], state_ptr->registers.array_access[0]);
	printf("$1  : %10d (0x%08x)\n", state_ptr->registers.array_access[1], state_ptr->registers.array_access[1]);
	printf("$2  : %10d (0x%08x)\n", state_ptr->registers.array_access[2], state_ptr->registers.array_access[2]);
	printf("$3  : %10d (0x%08x)\n", state_ptr->registers.array_access[3], state_ptr->registers.array_access[3]);
	printf("$4  : %10d (0x%08x)\n", state_ptr->registers.array_access[4], state_ptr->registers.array_access[4]);
	printf("$5  : %10d (0x%08x)\n", state_ptr->registers.array_access[5], state_ptr->registers.array_access[5]);
	printf("$6  : %10d (0x%08x)\n", state_ptr->registers.array_access[6], state_ptr->registers.array_access[6]);
	printf("$7  : %10d (0x%08x)\n", state_ptr->registers.array_access[7], state_ptr->registers.array_access[7]);
	printf("$8  : %10d (0x%08x)\n", state_ptr->registers.array_access[8], state_ptr->registers.array_access[8]);
	printf("$9  : %10d (0x%08x)\n", state_ptr->registers.array_access[9], state_ptr->registers.array_access[9]);
	printf("$10 : %10d (0x%08x)\n", state_ptr->registers.array_access[10], state_ptr->registers.array_access[10]);
	printf("$11 : %10d (0x%08x)\n", state_ptr->registers.array_access[11], state_ptr->registers.array_access[11]);
	printf("$12 : %10d (0x%08x)\n", state_ptr->registers.array_access[12], state_ptr->registers.array_access[12]);
	printf("PC  : %10d (0x%08x)\n", state_ptr->registers.struct_access.PC, state_ptr->registers.struct_access.PC);
	printf("CPSR: %10d (0x%08x)\n", state_ptr->registers.struct_access.CPSR, state_ptr->registers.struct_access.CPSR);
	printf("Non-zero memory:\n");

	uint32_t current_memory_location; 
	for (int i = 0; i < 65536; i += 4) {
		current_memory_location = 
				(state_ptr->memory[i+3]) + 
				(state_ptr->memory[i+2]<<8) + 
				(state_ptr->memory[i+1]<<16) + 
				(state_ptr->memory[i]<<24); 

		if (current_memory_location != 0) printf("0x%08x: 0x%08x\n", i, current_memory_location);
	}
}

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
	print_registers(state_ptr);

	free(state_ptr);
	return EXIT_SUCCESS;
}


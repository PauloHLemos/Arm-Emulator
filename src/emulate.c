#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "definitions.h"
#include "pipeline.h"
#include "loader.h"

void print_registers(struct State *state_ptr) {
	printf("Registers: \n");
	printf("$0   :\t\t%d\n", state_ptr->registers.array_access[0]);
	printf("$1   :\t\t%d\n", state_ptr->registers.array_access[1]);
	printf("$2   :\t\t%d\n", state_ptr->registers.array_access[2]);
	printf("$3   :\t\t%d\n", state_ptr->registers.array_access[3]);
	printf("$4   :\t\t%d\n", state_ptr->registers.array_access[4]);
	printf("$5   :\t\t%d\n", state_ptr->registers.array_access[5]);
	printf("$6   :\t\t%d\n", state_ptr->registers.array_access[6]);
	printf("$7   :\t\t%d\n", state_ptr->registers.array_access[7]);
	printf("$8   :\t\t%d\n", state_ptr->registers.array_access[8]);
	printf("$9   :\t\t%d\n", state_ptr->registers.array_access[9]);
	printf("$10  :\t\t%d\n", state_ptr->registers.array_access[10]);
	printf("$11  :\t\t%d\n", state_ptr->registers.array_access[11]);
	printf("$12  :\t\t%d\n", state_ptr->registers.array_access[12]);
	printf("$PC  :\t\t%d\n", state_ptr->registers.struct_access.PC);
	printf("$CPSR:\t\t%d\n", state_ptr->registers.struct_access.CPSR);

	// $0  :          0 (0x00000000)
	// $1  :          1 (0x00000001)
	// $2  :          3 (0x00000003)
	// $3  :          0 (0x00000000)
	// $4  :          0 (0x00000000)
	// $5  :          0 (0x00000000)
	// $6  :          0 (0x00000000)
	// $7  :          0 (0x00000000)
	// $8  :          0 (0x00000000)
	// $9  :          0 (0x00000000)
	// $10 :          0 (0x00000000)
	// $11 :          0 (0x00000000)
	// $12 :          0 (0x00000000)
	// PC  :         16 (0x00000010)
	// CPSR:          0 (0x00000000)
	// Non-zero memory:
	// 0x00000000: 0x0110a0e3
	// 0x00000004: 0x022081e2
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


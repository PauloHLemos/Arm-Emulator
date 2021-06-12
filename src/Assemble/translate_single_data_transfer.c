#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "split_instructions.h"
#include "instructions.h"
#include "definitions.h"


struct Instruction translate_single_data_transfer(char *instruction) {
	struct Instruction instruction_struct;
	instruction_struct.type = SINGLE_DATA_TRANSFER;
	instruction_struct.cond = ALWAYS;
	return instruction_struct;
}


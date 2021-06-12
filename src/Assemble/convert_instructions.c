#include <stdint.h>
#include <stdbool.h>
#include "definitions.h"
#include "encode.h"
#include "symbol_table.h"
#include "instructions.h"
#include "split_instructions.h"

bool is_multiply(char *opcode);
bool is_single_data_transfer(char *opcode);
bool is_branch(char *opcode);

uint32_t convert_instructions(char *instruction, struct ST_Node *st_head_ptr, uint32_t current_address) {
	struct Instruction instruction_struct;
	char opcode[3];
	extract_opcode(instruction, opcode);
	if (is_multiply(opcode)) {
		instruction_struct = translate_multiply(instruction);
	} else if (is_single_data_transfer(opcode)) {
		instruction_struct = translate_single_data_transfer(instruction);
	} else if (is_branch(opcode)) {
		instruction_struct = translate_branch(instruction, st_head_ptr, current_address);
	} else {
		instruction_struct = translate_data_processing(instruction, st_head_ptr);
	}
	return encode(instruction_struct);
}

bool is_multiply(char *opcode) {
	return opcode == "mul" || opcode == "mla";
}

bool is_single_data_transfer(char *opcode) {
	return opcode == "ldr" || opcode == "str";
}

bool is_branch(char *opcode) {
	return opcode == "beq" ||
		opcode == "bne" ||
		opcode == "bge" ||
		opcode == "blt" ||
		opcode == "bgt" ||
		opcode == "ble" ||
		opcode == "b";
}


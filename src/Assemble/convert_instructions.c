#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "definitions.h"
#include "encode.h"
#include "symbol_table.h"
#include "instructions.h"
#include "split_instructions.h"
#include "queue.h"

bool is_multiply(char *opcode) {
	return strcmp(opcode, "mul") == 0 || strcmp(opcode, "mla") == 0;
}

bool is_single_data_transfer(char *opcode) {
	return strcmp(opcode, "ldr") == 0 || strcmp(opcode, "str") == 0;
}

bool is_branch(char *opcode) {
	return strcmp(opcode, "beq") == 0 ||
	       strcmp(opcode, "bne") == 0 ||
	       strcmp(opcode, "bge") == 0 ||
	       strcmp(opcode, "blt") == 0 ||
	       strcmp(opcode, "bgt") == 0 ||
	       strcmp(opcode, "ble") == 0 ||
	       strcmp(opcode, "b")   == 0;
}

uint32_t convert_instructions(char *instruction, 
			      struct ST_Node *st_head_ptr, 
			      struct Queue_Node *queue_node_ptr, 
			      uint32_t current_address, 
			      uint32_t *end_address) {

	char opcode[10];
	extract_opcode(instruction, opcode);

	if (is_multiply(opcode)) {
		return encode(translate_multiply(instruction));
	} else if (is_single_data_transfer(opcode)) {
		return encode(translate_single_data_transfer(instruction, 
							     queue_node_ptr, 
							     current_address, 
							     end_address));
	} else if (is_branch(opcode)) {
		return encode(translate_branch(instruction, st_head_ptr, current_address));
	} else {
		return encode(translate_data_processing(instruction));
	}
}



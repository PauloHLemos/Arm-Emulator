#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "split_instructions.h"
#include "instructions.h"
#include "definitions.h"
#include "queue.h"

static void translate_num_const(struct Instruction *instruction_struct_ptr, char *address, struct Queue_Node *node, uint32_t curr_address, uint32_t *end_address) {
	address++;
	if (strtol(address, NULL, 0) < 0xff) {
		//call mov instruction
		char instruction[512];
		sprintf(instruction, "mov r%d, #%s", instruction_struct_ptr->rd, address);
		//printf("instr: %s\n", instruction);
		*instruction_struct_ptr = translate_data_processing(instruction);
	} else { 
		instruction_struct_ptr->immediate_offset = false; //true?
		instruction_struct_ptr->pre_post_indexing = true;
		instruction_struct_ptr->rn = 15;
		instruction_struct_ptr->offset = ((*end_address - curr_address) - 8);
		instruction_struct_ptr->up = true;
		add_queue_node(node, strtol(address, NULL, 0));			
		(*end_address) += 4;
		//set up bit	
	}	
}
static void translate_pre_indexed_immediate(struct Instruction *instruction_struct_ptr, char *address) {
	int offset = strtol(address, NULL, 0);
	instruction_struct_ptr->up = offset >= 0;
	instruction_struct_ptr->offset = abs(offset);
	instruction_struct_ptr->immediate_offset = false;
}
static void translate_pre_indexed_shifted_register(struct Instruction *instruction_struct_ptr, char *address) {

}

static void translate_pre_indexed(struct Instruction *instruction_struct_ptr, char *address) {
	instruction_struct_ptr->pre_post_indexing = true;
	address++;
	address[strlen(address) - 1] = '\0';
	if (strchr(address, ',') == NULL) {
		instruction_struct_ptr->rn = strtol(address + 1, NULL, 0);
		instruction_struct_ptr->offset = 0;
		instruction_struct_ptr->up = true;
		instruction_struct_ptr->immediate_offset = false;
	} else {
		char rn[sizeof(address)];
		strcpy(rn, address);

		int pos_separator = 0;
		for (; address[pos_separator] != ','; pos_separator++); 
		rn[pos_separator] = '\0';
		instruction_struct_ptr->rn = strtol(rn + 1, NULL, 0);

		for (address++; *address != '#' && *address != 'r'; address++);
		if (*address == '#') {
			address++;
			translate_pre_indexed_immediate(instruction_struct_ptr, address);

		} else if (*address == 'r') {
			address++;
			translate_pre_indexed_shifted_register(instruction_struct_ptr, address);
		}

	}
}

static void translate_post_indexed_immediate(struct Instruction *instruction_struct_ptr, char *address) {
	int offset = strtol(address, NULL, 0);
	instruction_struct_ptr->offset = abs(offset);
	instruction_struct_ptr->up = offset >= 0;
	instruction_struct_ptr->pre_post_indexing = false;
	instruction_struct_ptr->immediate_offset = true;
}

static void translate_post_indexed_shifted_register(struct Instruction *instruction_struct_ptr, char *address) {

}

static void translate_post_indexed(struct Instruction *instruction_struct_ptr, char *address) {
	address++;
	char rn[strlen(address)];
	strcpy(rn, address);
	
	int pos_separator = 0;
	for (; address[pos_separator] != '\0' && address[pos_separator] != ','; pos_separator++);
	rn[pos_separator] = '\0';
	instruction_struct_ptr->rn = strtol(rn + 1, NULL, 0);

	for (address++; *address != '#' && *address != 'r'; address++);
	if (*address == '#') {
		address++;
		translate_post_indexed_immediate(instruction_struct_ptr, address);

	} else if (*address == 'r') {
		address++;
		translate_post_indexed_shifted_register(instruction_struct_ptr, address);
	}
}

struct Instruction translate_single_data_transfer(char *instruction, struct Queue_Node *node, 
		uint32_t curr_address, uint32_t *end_address) {
	struct Instruction instruction_struct;
	memset(&instruction_struct, 0, sizeof(struct Instruction));
	// address size 504 allows lines of length 512 to be processed
	char opcode[10], rd[10], address[510];
	instruction_struct.type = SINGLE_DATA_TRANSFER;
	instruction_struct.cond = ALWAYS;
	split_3_arguments(instruction, opcode, rd, address);
	instruction_struct.load_store = strcmp(opcode, "ldr") == 0;
	instruction_struct.rd = strtol(rd + 1, NULL, 0);

	if (address[0] == '=') {
		translate_num_const(&instruction_struct, address, node, curr_address, end_address);
	} else if (address[strlen(address) - 1] == ']') {
		//pre-indexed address 
		translate_pre_indexed(&instruction_struct, address);
	} else {
		//post-indexed address
		translate_post_indexed(&instruction_struct, address);
	}

	instruction_struct.set_condition_codes = false;

	return instruction_struct;
}


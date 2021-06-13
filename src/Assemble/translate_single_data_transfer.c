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

static uint32_t toint(char* string) {
	bool neg;
	neg = string[0] == '-';
	if (neg) {
		string++;
	}
	assert(string != NULL);
	if (string[1] == 'x') {
		string += 2;
		return (uint32_t) strtol(string, NULL, 16);
	}
	return neg ? -atoi(string) : atoi(string);
}

static void translate_num_const(struct Instruction *instruction_struct_ptr, char *address, struct Queue_Node *node, 
		uint32_t curr_address, uint32_t end_address) {
	address++;
	if (toint(address) < 0xff) {
		//call mov instruction
		char instruction[512];
		sprintf(instruction, "mov r%d, #%s", instruction_struct_ptr->rd, address);
		//printf("instr: %s\n", instruction);
		*instruction_struct_ptr = translate_data_processing(instruction);
	} else {
		instruction_struct_ptr->immediate_offset = false; //true?
		instruction_struct_ptr->pre_post_indexing = true;
		instruction_struct_ptr->rn = 15;
		instruction_struct_ptr->offset = (end_address - curr_address + 4);
		instruction_struct_ptr->up = true;
		//add_node(node, toint(address));			
		*address++;
		//set up bit	
	}	
}

static void translate_pre_indexed(struct Instruction *instruction_struct_ptr, char *address) {
	address++;
	address[strlen(address) - 1] = '\0';
	//rn = strtok(rn, ",");
	if (strchr(address, ',') == NULL) {
		instruction_struct_ptr->rn = atoi(address + 1);
		instruction_struct_ptr->offset = 0;
		instruction_struct_ptr->up = true;
	} else {
		char rn[sizeof(address)];
		strcpy(rn, address);
		int pos_separator = 0;
		for (pos_separator; address[pos_separator] != '\0' && address[pos_separator] != ','; pos_separator++);
		rn[pos_separator] = '\0';
		address += (pos_separator + 2); 
		instruction_struct_ptr->rn = atoi(rn + 1);
		int offset = toint(address);
		instruction_struct_ptr->offset = abs(offset);
		instruction_struct_ptr->up = offset >= 0;
	}
	instruction_struct_ptr->pre_post_indexing = true;
	instruction_struct_ptr->immediate_offset = false;
}

static void translate_post_indexed(struct Instruction *instruction_struct_ptr, char *address) {
	address++;
	char rn[sizeof(address)];
	strcpy(rn, address);
	//rn = strtok(address, ",");
	int pos_separator = 0;
	for (pos_separator; address[pos_separator] != '\0' && address[pos_separator] != ','; pos_separator++);
	rn[pos_separator] = '\0';
	address += (pos_separator + 2);
	instruction_struct_ptr->rn = atoi(rn + 1);
	int offset = toint(address);
	instruction_struct_ptr->offset = abs(offset);
	instruction_struct_ptr->up = offset >= 0;
	
	instruction_struct_ptr->pre_post_indexing = false;
	instruction_struct_ptr->immediate_offset = false;
}

struct Instruction translate_single_data_transfer(char *instruction, struct QUEUE_Node *node, 
		uint32_t curr_address, uint32_t end_address) {
	struct Instruction instruction_struct;
	// address size 504 allows lines of length 512 to be processed
	char opcode[3], rd[4], address[504];
	instruction_struct.type = SINGLE_DATA_TRANSFER;
	instruction_struct.cond = ALWAYS;
	split_3_arguments(instruction, opcode, rd, address);
	instruction_struct.load_store = !(strcmp(opcode, "ldr"));
	instruction_struct.rd = atoi(rd + 1);

	if (address[0] == '=') {
		translate_num_const(&instruction_struct, address, node, curr_address, end_address);
	}
	else if (address[strlen(address) - 1] == ']') {
		//pre-indexed address 
		translate_pre_indexed(&instruction_struct, address);
	} else {
		//post-indexed address
		translate_post_indexed(&instruction_struct, address);
	}

	instruction_struct.set_condition_codes = false;
	instruction_struct.up = true;

	return instruction_struct;
}


#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "split_instructions.h"
#include "instructions.h"
#include "definitions.h"

static void translate_num_cons(struct Instruction *instruction_struct, char *expression) {
	// remove '='
	expression++;
	int val = atoi(expression);
	if (val <= 0xff) {
		// call mov instruction	
	} else {
	
		instruction_struct->pre_post_indexing = true;
	} 
}

static void translate_pre_indexed(struct Instruction *instruction_struct, char *expression) {
	expression++;
	if (strchr(expression, ',') != NULL) {
		instruction_struct->rn = atoi(strtok(expression, ","));
		char *offset = strtok(NULL, ","); 
		offset[strlen(offset) - 1] = '\0';
		instruction_struct->offset = atoi(offset);
	} else {
		instruction_struct->rn = atoi(expression);
		instruction_struct->offset = 0;
	} 
	instruction_struct->pre_post_indexing = true;
	intruction_struct->immediate_offset = false;
}


static void translate_post_indexed(struct Instruction *instruction_struct, char *expression) {
	expression++;
	char *rn = strtok(expression, ","); 
	rn[strlen(rn) - 1] = '\0';
	instruction_struct->rn = atoi(rn);
	instruction_struct->offset = atoi(strtok(NULL, ","));
	instruction_struct->pre_post_indexing = false;
	instructions_struct->immediate_offset = true;
}

struct Instruction translate_single_data_transfer(char *instruction) {
	struct Instruction instruction_struct;
	// address size 504 allows lines of length 512 to be processed
	char opcode[3], rd[4], address[504];
	instruction_struct.type = SINGLE_DATA_TRANSFER;
	extract_opcode(opcode, instruction);
	split_2_arguments_after_opcode(instruction, rd, address);
	if (address[0] == '=') {
		//numeric constant
		translate_num_cons(&instruction_struct, address);
	}
	else if (address[strlen(address) - 1] == ']') {
		//pre-indexed address 
		translate_pre_indexed(&instruction_struct, address);
	} else {
		//post-indexed address
		translate_post_indexed(&instruction_struct, address);
	}

	instruction_struct.rd = atoi(rd);
	instruction_struct.set_condition_codes = false;
	instruction_struct.load_store = ((opcode == "ldr") ? 1 : 0);
	instruction_struct.up = true;
	return instruction_struct;
}


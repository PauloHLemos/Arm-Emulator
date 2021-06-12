#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "split_instructions.h"
#include "instructions.h"
#include "definitions.h"

void translate_num_const(struct Instruction *instruction_struct_ptr, char *address) {
	address++;
	printf("heee\n");
	if (atoi(address) < 0xff) {
		//call mov instruction
		//use instruction_struct_ptr->rd
		//*instruction_struct_ptr = translate_data_processing(("mov %s, #%s", instruction_struct_ptr->rd, address));

		struct Instruction instr = translate_data_processing(("mov %s, #%s", instruction_struct_ptr->rd, address));
		printf("opcode: %d\n", instr.opcode);
	}	
	printf("here\n");
}

void translate_pre_indexed(struct Instruction *instruction_struct_ptr, char *address) {
	address++;
	address[strlen(address) - 1] = '\0';
	//rn = strtok(rn, ",");
	if (strchr(address, ',') == NULL) {
		instruction_struct_ptr->rn = atoi(address + 1);
		instruction_struct_ptr->offset = 0;
	} else {
		char rn[sizeof(address)];
		strcpy(rn, address);
		int pos_separator = 0;
		for (pos_separator; address[pos_separator] != '\0' && address[pos_separator] != ','; pos_separator++);
		rn[pos_separator] = '\0';
		address += (pos_separator + 2); 
		instruction_struct_ptr->rn = atoi(rn + 1);
		instruction_struct_ptr->offset = atoi(address);
	}
	instruction_struct_ptr->pre_post_indexing = true;
	instruction_struct_ptr->immediate_offset = false;
}

void translate_post_indexed(struct Instruction *instruction_struct_ptr, char *address) {
	address++;
	char rn[sizeof(address)];
	strcpy(rn, address);
	//rn = strtok(address, ",");
	int pos_separator = 0;
	for (pos_separator; address[pos_separator] != '\0' && address[pos_separator] != ','; pos_separator++);
	rn[pos_separator] = '\0';
	address += (pos_separator + 2);
	instruction_struct_ptr->rn = atoi(rn + 1);
	instruction_struct_ptr->offset = atoi(address);
	
	instruction_struct_ptr->pre_post_indexing = false;
	instruction_struct_ptr->immediate_offset = false;
}

struct Instruction translate_single_data_transfer(char *instruction) {
	struct Instruction instruction_struct;
	//address size ensures line of size 512 can be read
	char opcode[4], rd[4], address[504];
	instruction_struct.type = SINGLE_DATA_TRANSFER;
	instruction_struct.cond = ALWAYS;
	split_3_arguments(instruction, opcode, rd, address);
	instruction_struct.load_store = (opcode == "ldr");
	instruction_struct.rd = atoi(rd + 1);
	instruction_struct.up = true;

	if (address[0] == '=') {
		translate_num_const(&instruction_struct, address);
	}
	else if (address[strlen(address) - 1] == ']') {
		translate_pre_indexed(&instruction_struct, address);
	} else {
		translate_post_indexed(&instruction_struct, address);
	}

	instruction_struct.set_condition_codes = false;
      
	return instruction_struct;
}


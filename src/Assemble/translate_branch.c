#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "definitions.h"

struct Instruction translate_branch(char *instruction, struct ST_Node *st_head_ptr, uint32_t current_address){
	struct Instruction instruction_struct;
	uint32_t offset;
	char cond[4], expression[100];
	
	sscanf(instruction, "%s %s", cond, expression);
	
	instruction_struct.cond = search_table(st_head_ptr, cond);
	
	if (atoi(expression) == 0){
		offset = search_table(st_head_ptr, expression);
	}
	else{
		offset = atoi(expression);
	}
	offset = current_address > offset ? current_address - offset : offset - current_address;
	offset -= 8;
	instruction_struct.offset = offset;
	return instruction_struct;
	}

int main(void){
    return 0;
}

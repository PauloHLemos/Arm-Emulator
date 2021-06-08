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
	offset >>= 8;
	return instruction_struct;
	}

//int main(void){
//    char instruct[] = "bne 2341";
//    char *instruction = instruct;
//    uint32_t current_address= 2000;
//
//    uint32_t offset;
//    char cond[4], expression[100];
//    sscanf(instruction, "%s %s", cond, expression);
//    printf("%s\n", cond);
//    if (atoi(expression) == 0){
//        offset = 0;
//    }
//    else{
//        offset = atoi(expression);
//    }
//    offset = current_address > offset ? current_address - offset : offset - current_address;
//    offset -= 8;
//    printf("%d\n", offset);
//}

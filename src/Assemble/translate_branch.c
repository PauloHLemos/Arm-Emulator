#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "definitions.h"
#include "symbol_table.h"

struct Instruction translate_branch(char *instruction, struct ST_Node *st_head_ptr, uint32_t current_address){
	struct Instruction instruction_struct;
	uint32_t target_address;
	uint32_t offset;
	char cond[4], expression[100];

	sscanf(instruction, "%s %s", cond, expression);
	instruction_struct.cond = search_table(st_head_ptr, cond);
	if (atoi(expression) == 0){
		target_address = search_table(st_head_ptr, expression);
	}
	else{
		target_address = atoi(expression);
	}
	offset = target_address - current_address;
	offset -= 8; //pipeline offset
	offset >>= 2; //right shift two bits 
	instruction_struct.offset = offset;
	return instruction_struct;
	}

//int main(void){
//    char instruct[] = "bne 2341";
//    char *instruction = instruct;
//    uint32_t current_address= 2000;
//	  char *cond_ptr = cond;
//	  char *expression_ptr = expression;
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
//    offset = offset - current_address;
//    offset -= 8;
//    offset >>= 2;
//    printf("%d\n", offset);
//}

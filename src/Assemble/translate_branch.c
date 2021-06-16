#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "definitions.h"
#include "symbol_table.h"

struct Instruction translate_branch(char *instruction, struct ST_Node *st_head_ptr, uint32_t current_address){
        struct Instruction instruction_struct;
	memset(&instruction_struct, 0, sizeof(struct Instruction));
	instruction_struct.type = BRANCH;
        uint32_t target_address;
        int32_t offset;
        char cond[4], expression[100];

        sscanf(instruction, "%s %s", cond, expression);
        if (strcmp(cond, "beq") == 0) {instruction_struct.cond = EQUAL;}
        else if (strcmp(cond, "bne") == 0) {instruction_struct.cond = NOT_EQUAL;}
        else if (strcmp(cond, "bge") == 0) {instruction_struct.cond = GREATER_OR_EQUAL;}
        else if (strcmp(cond, "blt") == 0) {instruction_struct.cond = LESS_THAN;}
        else if (strcmp(cond, "bgt") == 0) {instruction_struct.cond = GREATER_THAN;}
        else if (strcmp(cond, "ble") == 0) {instruction_struct.cond = LESS_THAN_OR_EQUAL;}
        else if (strcmp(cond, "b") == 0) {instruction_struct.cond = ALWAYS;}
        else if (strcmp(cond, "bal") == 0) {instruction_struct.cond = ALWAYS;}

        if (atoi(expression) == 0){
		assert(search_table(st_head_ptr, expression, &target_address));
        }
        else{
		target_address = atoi(expression);
        }

        offset = target_address - current_address;
        offset -= 8; //pipeline offset
        offset >>= 2; //right shift two bits
        instruction_struct.offset = (uint32_t) (offset & 0xffffff);
        return instruction_struct;
}

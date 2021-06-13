#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"
#include "symbol_table.h"

struct Instruction translate_branch(char *instruction, struct ST_Node *st_head_ptr, uint32_t current_address){
        struct Instruction instruction_struct;
        uint32_t target_address;
        uint32_t offset;
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
//        char instruct[] = "bne 2341";
//        char *instruction = instruct;
//        uint32_t current_address= 2000;
//        char cond[4], expression[100];
//        uint32_t offset;
//
//        sscanf(instruction, "%s %s", cond, expression);
//        printf("%s\n", cond);
//        if (strcmp(cond, "beq") == 0) {printf ("EQUAL");}
//        if (strcmp(cond, "bne") == 0) {printf ("NOT_EQUAL");}
//        if (strcmp(cond, "bge") == 0) {printf ("GREATER_OR_EQUAL");}
//        if (strcmp(cond, "blt") == 0) {printf ("LESS_THAN");}
//        if (strcmp(cond, "bgt") == 0) {printf ("GREATER_THAN");}
//        if (strcmp(cond, "ble") == 0) {printf ("LESS_THAN_OR_EQUAL");}
//        if (strcmp(cond, "b") == 0) {printf ("ALWAYS");}
//        if (strcmp(cond, "bal") == 0) {printf ("ALWAYS");}
//        if (atoi(expression) == 0){
//            offset = 0;
//        }
//        else{
//            offset = atoi(expression);
//        }
//        offset = offset - current_address;
//        offset -= 8;
//        offset >>= 2;
//        printf("%d\n", offset);
//}

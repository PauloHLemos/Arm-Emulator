#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdint.h>
#include "symbol_table.h"


uint32_t translate_branch(char *instruction, struct ST_Node *st_head_ptr, uint32_t current_address);

uint32_t translate_data_processing(char *instruction, struct ST_Node *st_head_ptr);

uint32_t translate_single_data_transfer(char *instruction, struct ST_Node *st_head_ptr);

uint32_t translate_multiply(char *instruction, struct ST_Node *st_head_ptr);

uint32_t translate_single_data_transfer(char *instruction, struct ST_Node *st_head_ptr);

#endif

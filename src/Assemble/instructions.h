#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdint.h>
#include "symbol_table.h"
#include "definitions.h"
#include "queue.h"


struct Instruction translate_branch(char *instruction, struct ST_Node *st_head_ptr, uint32_t current_address);

struct Instruction translate_data_processing(char *instruction);

struct Instruction translate_single_data_transfer(char *instruction, 
						  struct Queue_Node* node,
						  uint32_t curr_address, 
						  uint32_t *end_address);

struct Instruction translate_multiply(char *instruction);

#endif

#ifndef CONVERT_INSTRUCTIONS_H
#define CONVERT_INSTRUCTIONS_H

#include <stdint.h>
#include "symbol_table.h"

uint32_t convert_instructions(char *instruction, struct ST_Node *st_head_ptr, uint32_t current_address, uint32_t end_address);

#endif

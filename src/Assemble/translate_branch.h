#ifndef TRANSLATE_BRANCH_H
#define TRANSLATE_BRANCH_H

#include <stdint.h>
#include "symbol_table.h"

uint32_t translate_branch(char *instruction, struct ST_Node *st_head_ptr, uint32_t current_address);

#endif

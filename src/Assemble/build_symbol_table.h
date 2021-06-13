#ifndef BUILD_SYMBOL_TABLE_H
#define BUILD_SYMBOL_TABLE_H

#include <stdio.h>
#include "symbol_table.h"

struct ST_Node *build_symbol_table(FILE *file_ptr, uint32_t *address_ptr);

#endif


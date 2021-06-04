#ifndef TRANSLATE_SINGLE_DATA_TRANSFER_H
#define TRANSLATE_SINGLE_DATA_TRANSFER_H

#include <stdint.h>
#include "symbol_table.h"

uint32_t translate_single_data_transfer(char *instruction, struct ST_Node *st_head_ptr);

#endif

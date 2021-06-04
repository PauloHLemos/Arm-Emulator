#ifndef TRANSLATE_DATA_PROCESSING_H
#define TRANSLATE_DATA_PROCESSING_H

#include <stdint.h>
#include "symbol_table.h"

uint32_t translate_data_processing(char *instruction, struct ST_Node *st_head_ptr);

#endif

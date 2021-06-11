#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "symbol_table.h"

void translate(FILE *stream, struct ST_Node *st_head_ptr, char *output_filename);

#endif

#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <stdio.h>
#include "symbol_table.h"

void translate(FILE *file_ptr, struct ST_Node *st_head_ptr, char *output_filename);

#endif
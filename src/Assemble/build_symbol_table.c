#include <stdio.h>
#include <stdlib.h>
#include "build_symbol_table.h"
#include "symbol_table.h"

struct ST_Node *build_symbol_table(FILE *file_ptr) {
	struct ST_Node *head_node_ptr = (struct ST_Node *) malloc(sizeof(struct ST_Node));
	return head_node_ptr;
}

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

struct ST_Node {
	char *label;
	uint32_t address;
	struct ST_Node *next_ptr;
};

<<<<<<< HEAD:src/Assemble/symbol_table.h
// uint32_t search_table(struct ST_Node *node, char *label);
// bool add_node(struct ST_Node *node, char *label, uint32_t address);

#endif
=======
uint32_t search_table(struct ST_Node *node, char *label);
void add_node(struct ST_Node *node, char *label, uint32_t address);
struct ST_Node *initialize();
void dealocate(struct ST_Node *node);
>>>>>>> implement_symbol_table_lib:src/Assemble/symbol_table/symbol_table.h

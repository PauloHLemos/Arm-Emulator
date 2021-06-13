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

uint32_t search_table(struct ST_Node *node, char *label);
void add_node(struct ST_Node *node, char *label, uint32_t address);
struct ST_Node *initialize();
void dealocate(struct ST_Node *node);

#endif

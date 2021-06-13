#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "symbol_table.h"
#include <stdio.h>

// returns address corresponding to label and -1 if label not found.
bool search_table(struct ST_Node *node, char *label, uint32_t *address_ptr) {
	while (node->label != label) {
		if (node->next_ptr == NULL) {
			return false;
		}
		node = node->next_ptr;
	}
	*address_ptr = node->address;
	return true;
}

void add_node(struct ST_Node *node, char *label, uint32_t address) {
	while (node->next_ptr != NULL) {
		node = node->next_ptr;
	}
	struct ST_Node *new_node = initialize();
	new_node->label = label;
	new_node->address = address;
	new_node->next_ptr = NULL;
	node->next_ptr = new_node;
}

static struct ST_Node* allocate_node() {
	struct ST_Node *node = malloc(sizeof(node));
	return node;
}

struct ST_Node* initialize() {
	struct ST_Node *node = allocate_node();
	node->label = "";
	return node;
}

void dealocate(struct ST_Node* node) {
	struct ST_Node *next;
	while (node != NULL) {
		next = node->next_ptr;
		free(node);
		node = next;
	}
}

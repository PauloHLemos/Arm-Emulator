#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "symbol_table.h"

// returns address corresponding to label and -1 if label not found.
bool search_table(struct ST_Node *node_ptr, char *label, uint32_t *address_ptr) {
	for (; strcmp(node_ptr->label, label) != 0; node_ptr = node_ptr->next_ptr) {
		if (node_ptr->next_ptr == NULL) return false;
	}
	*address_ptr = node_ptr->address;
	return true;
}

void add_node(struct ST_Node *node_ptr, char *label, uint32_t address) {
	for (; node_ptr->next_ptr != NULL; node_ptr = node_ptr->next_ptr);

	struct ST_Node *new_node_ptr = initialize();

	strcpy(new_node_ptr->label, label);
	new_node_ptr->address  = address;
	node_ptr->next_ptr     = new_node_ptr;
}

struct ST_Node* initialize() {
	return calloc(1, sizeof(struct ST_Node));
}

void deallocate(struct ST_Node* node_ptr) {
	for (struct ST_Node *next_ptr; node_ptr != NULL; next_ptr = node_ptr->next_ptr, 
							 free(node_ptr), 
							 node_ptr = next_ptr);
}

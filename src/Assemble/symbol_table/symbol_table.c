#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "symbol_table.h"
#include <stdio.h>

int main(void) {
	struct ST_Node head;
	head.label = "a";
	head.address = 0;
	head.next_ptr = NULL;

	add_node(&head, "b", 1);
	printf("%d\n", search_table(&head, "b"));
	printf("%d\n", search_table(&head, "a"));

	return 0;
}

// returns address corresponding to label and -1 if label not found.
uint32_t search_table(struct ST_Node *node, char *label) {
	while (node->label != label) {
		if (node->next_ptr == NULL) {
			return -1;
		}
		node = node->next_ptr;
	}
	return node->address;
}

// make return type void
bool add_node(struct ST_Node *node, char *label, uint32_t address) {
	/*
	 * while (node->next_ptr != NULL) {
		if (node->label == label) {
			return false;
		}
		node = node->next_ptr;
	}
	if (node->label = label) {
		return false;
	} */
	while (node->next_ptr != NULL) {
		node = node->next_ptr;
	}
	struct ST_Node new_node;
	new_node.label = label;
	new_node.address = address;
	new_node.next_ptr = NULL;
	node->next_ptr = &new_node;
	return true;
}


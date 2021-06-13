#include <assert.h>
#include "queue.h"

struct Queue_Node *get_queue_node(struct Queue_Node *node, uint32_t *binary_ptr) {
	assert(node != NULL);
	*binary_ptr = node->binary;
	struct Queue_Node *next_ptr = node->next_ptr;
	free(node);
	return next_ptr;
}

void add_queue_node(struct Queue_Node *node, uint32_t binary) {
	while (node->next_ptr != NULL) {
		node = node->next_ptr;
	}
	struct Queue_Node *new_node = initialize_queue();
	new_node->binary = binary;
	node->next_ptr = new_node;

}

static struct Queue_Node* allocate_queue_node() {
	struct Queue_Node *node = malloc(sizeof(node));
	return node;
}

struct Queue_Node *initialize_queue() {
	struct Queue_Node *node = allocate_queue_node();
	node->next_ptr = NULL;
	return node;
}


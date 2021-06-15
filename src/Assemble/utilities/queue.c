#include <assert.h>
#include "queue.h"

struct Queue_Node *get_queue_node(struct Queue_Node *node_ptr, uint32_t *binary_ptr) {
	assert(node_ptr != NULL);
	*binary_ptr		    = node_ptr->binary;
	struct Queue_Node *next_ptr = node_ptr->next_ptr;
	free(node_ptr);
	return next_ptr;
}

void add_queue_node(struct Queue_Node *node_ptr, uint32_t binary) {
	for (; node_ptr->next_ptr != NULL; node_ptr = node_ptr->next_ptr);
	struct Queue_Node *new_node_ptr = initialize_queue();
	new_node_ptr->binary		= binary;
	node_ptr->next_ptr		= new_node_ptr;

}

struct Queue_Node *initialize_queue() {
	return calloc(1, sizeof(struct Queue_Node));
}


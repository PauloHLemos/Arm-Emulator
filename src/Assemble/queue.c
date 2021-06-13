#include <assert.h>
#include "queue.h"

struct QUEUE_Node get_node(struct QUEUE_Node *node, uint32_t *binary_ptr) {
	assert(node != NULL);
	*binary_ptr = node->binary;
	struct QUEUE_Node next_ptr = node->next_ptr;
	free(node);
	return next_ptr;
}

void add_node(struct QUEUE_Node *node, uint32_t binary) {
	while (node->next_ptr != NULL) {
		node = node->next_ptr;
	}
	struct QUEUE_NODE *new_node = initialize();
	new_node->binary = binary;
	node->next_ptr = new_node;

}

static struct QUEUE_Node* allocate_node() {
	struct QUEUE_Node *node = malloc(sizeof(node));
	return node;
}

struct QUEUE_Node *initialize() {
	struct QUEUE_Node *node = allocate_node();
	node->next_ptr == NULL;
	return node;
}

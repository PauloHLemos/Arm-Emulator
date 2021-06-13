#ifndef QUEUE_H 
#define QUEUE_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

struct QUEUE_Node {
	uint32_t binary;
	struct QUEUE_Node *next_ptr;
};

struct QUEUE_Node get_queue_node(struct QUEUE_Node *node, uint32_t *binary_ptr);
void add_queue_node(struct QUEUE_Node *node, uint32_t binary);
struct QUEUE_Node *initialize_queue();

#endif


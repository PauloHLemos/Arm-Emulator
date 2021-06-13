#ifndef Queue_H 
#define Queue_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

struct Queue_Node {
	uint32_t binary;
	struct Queue_Node *next_ptr;
};

struct Queue_Node *get_queue_node(struct Queue_Node *node, uint32_t *binary_ptr);
void add_queue_node(struct Queue_Node *node, uint32_t binary);
struct Queue_Node *initialize_queue();

#endif


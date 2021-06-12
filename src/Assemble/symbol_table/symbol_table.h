#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

struct ST_Node {
	char *label;
	uint32_t address;
	struct ST_Node *next_ptr;
};

bool search_table(struct ST_Node *node, char *label, uint32_t *address_ptr);
void add_node(struct ST_Node *node, char *label, uint32_t address);
struct ST_Node *initialize();
void dealocate(struct ST_Node *node);

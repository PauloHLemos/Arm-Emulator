#include <stdint.h>
#include <stdbool.h>

struct ST_Node {
	char *label;
	uint32_t address;
	struct ST_Node *next_ptr;
};

uint32_t search_table(struct ST_Node *node, char *label);
void add_node(struct ST_Node *node, char *label, uint32_t address);


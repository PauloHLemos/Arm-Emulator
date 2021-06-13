#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "build_symbol_table.h"
#include "symbol_table.h"

struct ST_Node *build_symbol_table(FILE *stream, uint32_t *address_ptr) {
	struct ST_Node* head = initialize();
	// head->address
	char *label;
	uint32_t address = 0;
	int max_line_length = 512;
	char buffer[max_line_length];

	while(fgets(buffer, max_line_length, stream)) {
		buffer[strcspn(buffer, "\n")] = 0;
		if (strchr(buffer, ':') != NULL) {
			label = strtok(buffer, ":");
			add_node(head, label, address);	
		} else {
			address += 4;
		}		
	}
	*address_ptr = address;
	return head;
}

// int main() {
// 	printf("Working\n");
// 	return 0;
// }

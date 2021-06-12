#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "build_symbol_table.h"
#include "symbol_table.h"

struct ST_Node *build_symbol_table(FILE *stream) {
	struct ST_Node* head = initialize();
	// head->address
	char *label;
	uint32_t address = 0;
	int max_line_length = 512;
	char buffer[max_line_length];

	while(fgets(buffer, max_line_length, stream)) {
		label = strtok(buffer, ":");
		if (label != NULL) {
			add_node(head, label, address);	
		}		
		address += 4;
	}
	return head;
}

int main() {
	printf("Working\n");
	return 0;
}

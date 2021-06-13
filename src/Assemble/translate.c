#include <stdint.h>
#include <stdbool.h>
#include "binary_file_writer.h"
#include "convert_instruction.h"
#include "symbol_table.h"

bool is_label(char *instruction);

void translate(FILE *stream, struct ST_Node *st_head_ptr, char *output_filename, uint32_t end_address) {
	int max_line_length = 512;
	char buffer[max_line_length];
	uint32_t current_address = 0;
	uint32_t translated_instruction;
	FILE *output_stream = open_file(output_filename);

	while(fgets(buffer, max_line_length, stream)) {
		if (!is_label(buffer)) {
			translated_instruction = convert_instruction(buffer, st_head_ptr, current_address);
			binary_file_writer(output_stream, &translated_instruction);
			current_address += 4;
		}		
	}
	close_file(output_stream);
}

bool is_label(char *instruction) {
	return strchr(instruction, ':') != NULL;
}

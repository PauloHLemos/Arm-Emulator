#include <stdint.h>
#include <stdbool.h>
#include "binary_file_writer.h"
#include "convert_instruction.h"
#include "symbol_table.h"

bool is_label(char *instruction);

uint32_t reverse_bytes(uint32_t bytes);

void translate(FILE *stream, struct ST_Node *st_head_ptr, char *output_filename) {
	int max_line_length = 512;
	char buffer[max_line_length];
	uint32_t current_address = 0;
	uint32_t translated_instruction;
	FILE *output_stream = open_file(output_filename);

	while(fgets(buffer, max_line_length, stream)) {
		if (!is_label(buffer)) {
			translated_instruction = convert_instruction(buffer, st_head_ptr, current_address);
			binary_file_writer(output_stream, reverse_bytes(translated_instruction));
			current_address += 4;
		}		
	}
	close_file(output_stream);
}

uint32_t reverse_bytes(uint32_t bytes) {
	int32_t temp = input << 24;
	temp = temp | ((input & 0b1111111100000000) << 8);
	temp = temp | ((input >> 8) & 0b1111111100000000);
	temp = temp | ((input >> 24) & 0b11111111);
	return temp;
}

bool is_label(char *instruction) {
	return strchr(instruction, ':') != NULL;
}

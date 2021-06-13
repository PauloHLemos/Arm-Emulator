#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "binary_file_writer.h"
#include "convert_instructions.h"
#include "symbol_table.h"
#include "queue.h"

bool is_label(char *instruction);
uint32_t reverse_bytes(uint32_t bytes);

void translate(FILE *stream, struct ST_Node *st_head_ptr, char *output_filename, uint32_t *end_address) {
	int max_line_length = 512;
	char buffer[max_line_length];
	uint32_t current_address = 0;
	uint32_t translated_instruction;
	FILE *output_stream = open_file(output_filename);
	struct Queue_Node *queue_node_ptr = initialize_queue();

	while(!feof(stream)) {
		fgets(buffer, max_line_length, stream);
		buffer[strcspn(buffer, "\n")] = 0;
		if (!is_label(buffer)) {
			translated_instruction = convert_instructions(buffer, st_head_ptr, queue_node_ptr, 
				current_address, end_address);
			uint32_t reversed_translated_instruction = reverse_bytes(translated_instruction);
			binary_file_writer(output_stream, &reversed_translated_instruction);
			current_address += 4;
		}		
	}
	uint32_t binary;
	queue_node_ptr = get_queue_node(queue_node_ptr, &binary);
	while (queue_node_ptr != NULL) {
		queue_node_ptr = get_queue_node(queue_node_ptr, &binary);
		binary_file_writer(output_stream, &binary);
	}
	close_file(output_stream);
}

uint32_t reverse_bytes(uint32_t bytes) {
	int32_t temp = bytes << 24;
	temp |= ((bytes & 0b1111111100000000) << 8);
	temp |= ((bytes >> 8) & 0b1111111100000000);
	temp |= ((bytes >> 24) & 0b11111111);
	return temp;
}

bool is_label(char *instruction) {
	return strchr(instruction, ':') != NULL;
}

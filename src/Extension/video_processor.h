#include <stdint.h>
#include "definitions.h"

void process_video(const char* input_path, const char* output_path, int buffer_size, 
	uint8_t *(*func_ptr)(Frame_Buffer *));

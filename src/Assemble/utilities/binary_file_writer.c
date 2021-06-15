#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "binary_file_writer.h"

void binary_file_writer(FILE *file_ptr, uint32_t *word_ptr){
        fwrite(word_ptr, 1, 4, file_ptr);
}

FILE *open_file(char *binary_fname){
	FILE *file_ptr = fopen(binary_fname, "wb");
	if (file_ptr == NULL) {
			perror("Error opening file.txt!");
			exit(1);
	}
	return file_ptr;
}

void close_file(FILE *file_ptr){
	fclose(file_ptr);	
}

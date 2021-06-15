#ifndef BINARY_FILE_WRITER_H
#define BINARY_FILE_WRITER_H

#include <stdio.h>

FILE *open_file(char *binary_fname);
void close_file(FILE *file_ptr);
void binary_file_writer(FILE *file_ptr, uint32_t *word_ptr);

#endif

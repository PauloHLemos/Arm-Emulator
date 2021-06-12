#ifndef BINARY_FILE_WRITER_H
#define BINARY_FILE_WRITER_H

FILE *open_file_stream();
bool close_file_stream(FILE *stream);
bool write_word(FILE *stream, uint32_t word);

#endif

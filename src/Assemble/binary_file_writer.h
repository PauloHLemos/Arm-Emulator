#ifndef BINARY_FILE_WRITER_H
#define BINARY_FILE_WRITER_H

[stream obj] open_file_stream();
bool close_file_stream([stream obj]);
bool write_word([stream obj] file_stream, uint32_t word);

#endif

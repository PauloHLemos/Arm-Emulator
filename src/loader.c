#include <stdint.h>
#include "definitions.h"

void loader(char *fname, uint32_t *memory){
	FILE *file = fopen(fname,"rb");
	if (file == NULL) {
		perror("Error opening file.txt!");
		exit(EXIT_FAILURE);
	}
	size_t size = fread(memory, 16384, 4, file);    
	if (ferror(file)){
		perror("Error reading from stream.\n");
		exit(EXIT_FAILURE);	
	}	
	fclose(fp);
}


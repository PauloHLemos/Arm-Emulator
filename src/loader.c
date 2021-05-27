#include <stdint.h>
#include <stdio.h>
#include "definitions.h"

void loader(char *fname, uint32_t *memory){
		FILE *file = fopen(fname,"rb");
		if (file == NULL) {
				perror("Error opening file.txt!");
				exit(1);
		}
		size_t size = fread(memory, 4, 16384, file);    
		if (ferror(file)){
				perror("Error reading from stream.\n");
				exit(1);	
		}	
		fclose(file);
}

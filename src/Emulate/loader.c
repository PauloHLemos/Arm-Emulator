#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"

void loader(char *fname, uint8_t *memory){
		FILE *file = fopen(fname,"rb");
		if (file == NULL) {
				perror("Error opening file.txt!");
				exit(1);
		}
		fread(memory, 1, 65536, file);    
		if (ferror(file)){
				perror("Error reading from stream.\n");
				exit(1);	
		}	
		fclose(file);
}

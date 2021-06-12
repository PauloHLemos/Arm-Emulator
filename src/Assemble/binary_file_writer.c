#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

FILE *open_file(char *binary_fname){
		FILE *file = fopen(binary_fname, "wb");
		if (file == NULL) {
				perror("Error opening file.txt!");
				exit(1);
		}
		return file;
};

void close_file(FILE *file){
		fclose(file);	
};

void binary_file_writer(FILE *file, uint32_t *word){
		//Using fixed sized types, 1 byte is 8 bits
		size_t size = fwrite(word, 1, 4, file); 
}

int main(void){
		printf("gg");
		close_file(open_file(("test01")));
		printf("gg");
		uint32_t number = 1234;
		uint32_t *word;
		word = &number;
		printf("gg");
		binary_file_writer(open_file(("test01")), word);
		return 0;
}

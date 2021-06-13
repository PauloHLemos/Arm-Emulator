#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void binary_file_writer(char *binary_fname, uint32_t *word){
        FILE *binary_file = fopen(binary_fname, "ab");
        if (binary_file == NULL) {
            perror("Error opening file.txt!");
            exit(1);
        }
        size_t size = fwrite(word, 1, 4, binary_file);
        fclose(file);
}

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

int main(void){
		printf("gg");
		printf("gg");
		uint32_t number = 1234;
		uint32_t *word;
		word = &number;
		printf("gg");
		FILE *file = open_file(("test01"));
		binary_file_writer(file, word);
		binary_file_writer(file, word);
		binary_file_writer(file, word);
		close_file(open_file(("test01")));
		return 0;
}

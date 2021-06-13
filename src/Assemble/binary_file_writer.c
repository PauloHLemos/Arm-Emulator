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

int main(void){
		uint32_t number = 0b11111111;
        uint32_t *word;
        word = &number;
        binary_file_writer("test01", word);
        number = 0b1;
        binary_file_writer("test01", word);
        return 0;
}

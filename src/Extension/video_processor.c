#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include "definitions.h"
// #include "video_processor.h"

static int get_width(const char* input_path) {
	char get_dim_command[200];
	sprintf(get_dim_command, "ffprobe -v error -select_streams v:0 -show_entries stream=width -of csv=s=x:p=0 %s", input_path);

	FILE *dim_file;
	char dimension[200];

	dim_file = popen(get_dim_command, "r");
	assert(dim_file != NULL);
	fgets(dimension, sizeof(dimension), dim_file);
	pclose(dim_file);
	return atoi(dimension);
}

static int get_height(const char* input_path) {
	char get_dim_command[200];
	sprintf(get_dim_command, "ffprobe -v error -select_streams v:0 -show_entries stream=height -of csv=s=x:p=0 %s", input_path);

	FILE *dim_file;
	char dimension[200];

	dim_file = popen(get_dim_command, "r");
	assert(dim_file != NULL);
	fgets(dimension, sizeof(dimension), dim_file);
	pclose(dim_file);
	return atoi(dimension);
}

void process_video(const char* input_path, const char* output_path, int buffer_size /*, array of function pointers*/) {
	int x, y, count;
	int width = get_width(input_path);
	int height = get_height(input_path);

	char make_output_file_command[200];
	char in_command[200];
	char out_command[200];
	
	sprintf(make_output_file_command, "rm %s; touch %s; chmod +rwx %s\n", output_path, output_path, output_path);
	sprintf(in_command, "ffmpeg -i %s -f image2pipe -vcodec rawvideo -pix_fmt rgb24 -", input_path);
	sprintf(out_command, "ffmpeg -y -f rawvideo -vcodec rawvideo -pix_fmt rgb24 -s 1280x720 -r 25 -i - -f mp4 -q:v 5 -an -vcodec mpeg4 %s", output_path);

	printf("make output file command: %s\n", make_output_file_command);
	printf("in command: %s\n", in_command);
	printf("out command: %s\n", out_command);
	
	// Open an input pipe from ffmpeg and an output pipe to a second instance of ffmpeg
	system(make_output_file_command);
	FILE *pipein = popen(in_command, "r");
	assert(pipein != NULL);
	FILE *pipeout = popen(out_command, "w");
	assert(pipeout != NULL);

	uint8_t frame[height * width * 3];
	// apparently just this declaration by itself breaks the code
	// uint8_t frame_buffer[buffer_size][height * width * 3];
	uint8_t *buffer[buffer_size];
	for (int i = 0; i < buffer_size; i++) {
		buffer[i] = (uint8_t *) malloc(height * width * 3 * sizeof(uint8_t));
	}

	int buffer_index = 0;
	for (count = fread(frame, 1, height * width * 3, pipein);
		count  == height * width * 3; count = fread(frame, 1, height * width * 3, pipein)) {

		buffer[buffer_index] = frame;
		
		for (int i = 0 ; i < width * height * 3; ++i) {
		    buffer[buffer_index][i] = 255 - buffer[buffer_index][i];
		}
		 
		fwrite(buffer[buffer_index], 1, height * width * 3, pipeout);
		buffer_index = (buffer_index + 1) % buffer_size;
	}

	// Flush and close input and output pipes
	fflush(pipein);
	pclose(pipein);
	fflush(pipeout);
	pclose(pipeout);
}

int main(void) {
	process_video("samples/teapot.mp4", "samples/test_output.mp4", 3);	
}

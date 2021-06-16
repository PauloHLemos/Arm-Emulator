#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "definitions.h"

// Video resolution
#define W 1280
#define H 720
 
// Allocate a buffer to store one frame
unsigned char frame[H][W][3] = {0};
 
void process_video(const char* input_path, const char* output_path /*, array of function pointers*/) {
	int x, y, count;

	// Open an input pipe from ffmpeg and an output pipe to a second instance of ffmpeg
	
	char make_output_file_command[200];
	char in_command[200];
	char out_command[200];
	
	sprintf(make_output_file_command, "rm %s; touch %s; chmod +rwx %s\n", output_path, output_path, output_path);
	sprintf(in_command, "ffmpeg -i %s -f image2pipe -vcodec rawvideo -pix_fmt rgb24 -", input_path);
	sprintf(out_command, "ffmpeg -y -f rawvideo -vcodec rawvideo -pix_fmt rgb24 -s 1280x720 -r 25 -i - -f mp4 -q:v 5 -an -vcodec mpeg4 %s", output_path);
	printf("make output file command: %s\n", make_output_file_command);
	printf("in command: %s\n", in_command);
	printf("out command: %s\n", out_command);
	system(make_output_file_command);
	FILE *pipein = popen(in_command, "r");
	assert(pipein != NULL);
	FILE *pipeout = popen(out_command, "w");
	assert(pipeout != NULL);

	for (count = fread(frame, 1, H*W*3, pipein); count  == H*W*3; count = fread(frame, 1, H*W*3, pipein)) {

		for (y=0 ; y<H ; ++y) for (x=0 ; x<W ; ++x) {
		    // Invert each colour component in every pixel
		    frame[y][x][0] = 255 - frame[y][x][0]; // red
		    frame[y][x][1] = 255 - frame[y][x][1]; // green
		    frame[y][x][2] = 255 - frame[y][x][2]; // blue
		}
		 
		// Write this frame to the output pipe
		fwrite(frame, 1, H*W*3, pipeout);
	}

	// Flush and close input and output pipes
	fflush(pipein);
	pclose(pipein);
	fflush(pipeout);
	pclose(pipeout);
}

int main(void) {
	process_video("samples/teapot.mp4", "samples/test_output.mp4");	
}

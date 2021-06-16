#include <stdlib.h>
#include <stdio.h>
#include "definitions.h"

// Video resolution
#define W 1280
#define H 720
 
// Allocate a buffer to store one frame
unsigned char frame[H][W][3] = {0};
 
void process_video(const char* input_path, const char* output_path /*, array of function pointers*/) {
	int x, y, count;

	// Open an input pipe from ffmpeg and an output pipe to a second instance of ffmpeg
	char in_command[200];
	char out_command[200];
	sprintf(in_command, "ffmpeg -i %s -f image2pipe -vcodec rawvideo -pix_fmt rgb24 -", input_path);
	sprintf(out_command,"ffmpeg -y -f rawvideo -vcodec rawvideo -pix_fmt rgb24 -s 1280x720 -r 25 -i - -f mp4 -q:v 5 -an -vcodec mpeg4 %s", output_path);
	FILE *pipein = popen(in_command, "r");
	FILE *pipeout = popen(out_command, "w");

	// Process video frames
	for (count = fread(frame, 1, H*W*3, pipein); count  == H*W*3;) {
		// Process this frame
		for (y=0 ; y<H ; ++y) for (x=0 ; x<W ; ++x)
		{
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
	process_video("samples/some.mov", "samples/output.mov");	
}

#include <assert.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "image_loader.h"

Frame *load_image(const char *image_path, int desired_channels) {
	
	int width, height, orig_num_channels;

	uint8_t* img = stbi_load(image_path, &width, &height, &orig_num_channels, desired_channels);
	assert(img != NULL);
	if (desired_channels == 0) {
		desired_channels = orig_num_channels;
	}
	printf("Succesfully loaded image of %d channels, into representation with %d channels\n", 
		orig_num_channels, desired_channels);

	Frame *frame_ptr = malloc(sizeof(*frame_ptr));
	frame_ptr->width = width;
	frame_ptr->height = height;
	frame_ptr->num_channels = desired_channels;
	frame_ptr->img = img;

	return frame_ptr;
}


Frame *load_rgb(const char *image_path) {
	return load_image(image_path, 3);
}
Frame *load_greyscale(const char* image_path) {	
	return load_image(image_path, 1);
}
Frame *load_full(const char* image_path){
	return load_image(image_path, 0);
}

/*
int main(void) {
	Frame *frame_ptr = load_image("samples/aeroplane.png", 3);
	printf("width: %d, height %d, num_channel:s %d, size of arr: %ld.\n", frame_ptr->width, frame_ptr->height, 
		frame_ptr->num_channels, sizeof(frame_ptr->img));
	return 0;
}
*/

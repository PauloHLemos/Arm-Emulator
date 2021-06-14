#include <assert.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "image_loader.h"

struct Frame *load_image(const char *image_path, int desired_channels) {
	
	int width, height, orig_num_channels;

	uint8_t* img = stbi_load("image.png", &width, &height, &orig_num_channels, desired_channels);
	assert(img != NULL);
	if (desired_channels == 0) {
		desired_channels = orig_num_channels;
	}
	printf("Succesfully loaded image of %d channels, into representation with %d channels\n", 
		orig_num_channels, desired_channels);

	struct Frame *frame = malloc(sizeof(frame));
	frame->width = width;
	frame->height = height;
	frame->num_channels = desired_channels;
	frame->img = img;

//	stbi_image_free(rgb_image);

	return frame;
}


struct Frame *load_rgb(const char *image_path) {
	return load_image(image_path, 3);
}
struct Frame *load_greyscale(const char* image_path) {	
	return load_image(image_path, 1);
}
struct Frame *load_full(const char* image_path){
	return load_image(image_path, 0);
}

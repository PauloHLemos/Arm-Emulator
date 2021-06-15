#include <assert.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#include "image_storer.h"

struct Frame *store_image(struct Frame *frame_ptr, const char *store_path) {
	stbi_write_png(store_path, frame_ptr->width, frame_ptr->height, frame_ptr->num_channels, frame_ptr->img,
		frame_ptr->width * frame_ptr->num_channels);
	stbi_image_free(frame_ptr->img);
	free(frame_ptr);
}

#include <assert.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#include "image_storer.h"

struct Frame *store_image(struct Frame *frame, const char *store_path) {
	stbi_write_png(store_path, frame->width, frame->height, frame->num_channels, frame->img,
		frame->width * frame->num_channels);
	stbi_image_free(frame->img);
	free(frame);
}

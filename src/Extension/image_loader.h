#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H
#include "definitions.h"

Frame *load_image(const char *image_path, int num_channels);
Frame *load_rgb(const char *image_path);
Frame *load_greyscale(const char* image_path);
Frame *load_full(const char* image_path);

#endif

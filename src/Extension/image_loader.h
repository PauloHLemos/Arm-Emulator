#include "definitions.h"

FRAME *load_image(const char *image_path, int num_channels);
FRAME *load_rgb(const char *image_path);
FRAME *load_greyscale(const char* image_path);
FRAME *load_full(const char* image_path);

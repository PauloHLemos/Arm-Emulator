#include "definitions.h"

struct Frame *load_image(const char *image_path, int num_channels);
struct Frame *load_rgb(const char *image_path);
struct Frame *load_greyscale(const char* image_path);
struct Frame *load_full(const char* image_path);

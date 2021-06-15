#include <stdint.h>
#include "definitions.h"

void add_images(frame *frame1, frame *frame2);

void subtract_images(frame *frame1, frame *frame2);

void multiply_image(frame *frame, float multiple);

void lower_threshold_image(frame *frame, uint8_t threshold);

void bitmask_image(frame *frame, frame *bitmask);

void print_image(frame *frame);

frame rgb_to_greyscale(frame *frame);

frame convolve_image(frame *frame, int kernel[5][5]);

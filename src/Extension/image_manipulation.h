#include <stdint.h>
#include "definitions.h"

void add_images(Frame *frame1_ptr, Frame *frame2_ptr);

void subtract_images(Frame *frame1_ptr, Frame *frame2_ptr);

void multiply_image(Frame *frame_ptr, float multiple);

void one_to_three_channels(Frame *frame_ptr);

void lower_threshold_image(Frame *frame_ptr, uint8_t threshold);

void bitmask_image(Frame *frame_ptr, Frame *bitmask_ptr);

void print_image(Frame *frame_ptr);

Frame rgb_to_greyscale(Frame *frame_ptr);

Frame convolve_image(Frame *frame_ptr, int cols, double **kernel);

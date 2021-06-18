#include <stdint.h>
#include "definitions.h"

void add_images(Frame *frame1_ptr, Frame *frame2_ptr);

void subtract_images(Frame *frame1_ptr, Frame *frame2_ptr);

void multiply_image(Frame *frame_ptr, float multiple);

void one_to_three_channels(Frame *frame_ptr);

void lower_threshold_image(Frame *frame_ptr, uint8_t threshold);

void bitmask_image(Frame *frame_ptr, Frame *bitmask_ptr);

void invert_bitmask(Frame *bitmask_ptr);

void fill_left(Frame *frame_ptr, Frame *mask_ptr, uint8_t threshold);

void fill_right(Frame *frame_ptr, Frame *mask_ptr, uint8_t threshold);

void absolute_difference(Frame *frame1_ptr, Frame *frame2_ptr);

void print_image(Frame *frame_ptr);

Frame rgb_to_greyscale(Frame *frame_ptr);
void rgb_to_greyscale_direct(Frame *frame_ptr);

Frame convolve_image(Frame *frame_ptr, int cols, double kernel[][cols]);
void convolve_image_direct(Frame *frame_ptr, int cols, double kernel[][cols]);

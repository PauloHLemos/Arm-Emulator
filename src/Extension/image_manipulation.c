#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "definitions.h"
#include "image_manipulation.h"

uint8_t *get_pixel_ptr(Frame *frame_ptr, int x, int y) {
        int index = x + y * frame_ptr->width;
        return (frame_ptr->img + index);
}

uint8_t get_pixel(Frame *frame_ptr, int x, int y) {
        if (x < 0 || x >= frame_ptr->width || y < 0 || y >= frame_ptr->height) 
                return 0;
        return *get_pixel_ptr(frame_ptr, x, y);
}

void set_pixel(Frame *frame_ptr, uint8_t value, int x, int y) {
        *get_pixel_ptr(frame_ptr, x, y) = value;
}

void add_images(Frame *frame1_ptr, Frame *frame2_ptr) {
        uint8_t new_value;
        for (int y = 0; y < frame1_ptr->height; y++) {
                for (int x = 0; x < frame1_ptr->width; x++) {
                        new_value = get_pixel(frame1_ptr, x, y) + get_pixel(frame2_ptr, x, y);
                        set_pixel(frame1_ptr, new_value, x, y);
                } } } 
void subtract_images(Frame *frame1_ptr, Frame *frame2_ptr) {
        uint8_t new_value;
        for (int y = 0; y < frame1_ptr->height; y++) {
                for (int x = 0; x < frame1_ptr->width; x++) {
                        new_value = get_pixel(frame1_ptr, x, y) - get_pixel(frame2_ptr, x, y);
                        set_pixel(frame1_ptr, new_value, x, y);
                }
        }
}

void multiply_image(Frame *frame_ptr, float multiple) {
	uint8_t new_value;
	for (int y = 0; y < frame_ptr->height; y++) {
                for (int x = 0; x < frame_ptr->width; x++) {
                        new_value = round(get_pixel(frame_ptr, x, y) * multiple);
                        set_pixel(frame_ptr, new_value, x, y);
                }
        }
}

void lower_threshold_image(Frame *frame_ptr, uint8_t threshold) {
        for (int y = 0; y < frame_ptr->height; y++) {
                for (int x = 0; x < frame_ptr->width; x++) {
                        if (get_pixel(frame_ptr, x, y) < threshold)
                                set_pixel(frame_ptr, 0, x, y);
                }
        }
}

void bitmask_image(Frame *frame_ptr, Frame *bitmask) {
        for (int y = 0; y < frame_ptr->height; y++) {
                for (int x = 0; x < frame_ptr->width; x++) {
                        if (get_pixel(bitmask, x, y) == 0)
                                set_pixel(frame_ptr, 0, x, y);
                }
        }
}

void print_image(Frame *frame_ptr) {
        for (int y = 0; y < frame_ptr->height; y++) {
                for (int x = 0; x < frame_ptr->width; x++) {
                        printf("%d", get_pixel(frame_ptr, x, y));
                }
                printf("\n");
        }
}

void fill_left(Frame *frame_ptr, Frame *mask_ptr, uint8_t threshold) {
        for (int y = 0; y < frame_ptr->height; y++) {
                for (int x = 0; x < frame_ptr->width; x++) {
                        if (get_pixel(frame_ptr, x, y) > threshold) {
				break;
			} else {
				set_pixel(mask_ptr, 1, x, y);
			}
                }
        }
}


void fill_right(Frame *frame_ptr, Frame *mask_ptr, uint8_t threshold) {
        for (int y = 0; y < frame_ptr->height; y++) {
                for (int x = frame_ptr->width - 1; x >= 0; x--) {
                        if (get_pixel(frame_ptr, x, y) > threshold) {
				break;
			} else {
				set_pixel(mask_ptr, 1, x, y);
			}
                }
        }
}

Frame rgb_to_greyscale(Frame *frame_ptr) {
	Frame grey;
	grey.img          = calloc(frame_ptr->width * frame_ptr->height, sizeof(uint8_t));
	grey.width        = frame_ptr->width;
	grey.height       = frame_ptr->height;
	grey.num_channels = 1;
	for (int i = 0; i < frame_ptr->width * frame_ptr->height; i++) {
		uint8_t average_colour = round((frame_ptr->img[3 * i] + 
						frame_ptr->img[3 * i + 1] + 
		        			frame_ptr->img[3 * i + 2]) / 3);
		grey.img[i] = average_colour;
	}

	return grey;
}

Frame convolve_image(Frame *frame_ptr, int cols, double kernel[][cols]) {
	assert(frame_ptr->num_channels == 1);
        double new_value;
        Frame convolved_image;
	convolved_image.img	     = calloc(frame_ptr->width * frame_ptr->height, sizeof(uint8_t));
	convolved_image.width  	     = frame_ptr->width;
	convolved_image.height 	     = frame_ptr->height;
	convolved_image.num_channels = 1;

	uint8_t max_offset = cols / 2;

        for (int y = 0; y < frame_ptr->height; y++) {
                for (int x = 0; x < frame_ptr->width; x++) {
                        new_value = 0;
                        for (int y_off = -1 * max_offset; y_off <= max_offset; y_off++) {
                                for (int x_off = -1 * max_offset; x_off <= max_offset; x_off++) {
                                        new_value += kernel[max_offset + y_off][max_offset + x_off] * 
						     get_pixel(frame_ptr, x + x_off, y + y_off);
                                }
                        }
                        set_pixel(&convolved_image, new_value, x, y);
                }
        }
        return convolved_image;
}

// int main()
// {
//         printf("hello world");
//         Frame frame;
//         frame.width = 2;
//         frame.height = 2;
//         frame.img = calloc(frame.width * frame.height, sizeof(uint8_t));
//         frame.img[0] = 2;
//         frame.img[1] = 4;
//         frame.img[2] = 8;
//         frame.img[3] = 9;
//         
//         Frame oframe;
//         oframe.width = 2;
//         oframe.height = 2;
//         oframe.img = calloc(frame.width * frame.height, sizeof(uint8_t));
//         oframe.img[0] = 1;
//         oframe.img[1] = 1;
//         oframe.img[2] = 1;
//         oframe.img[3] = 1;
//         
//         int kernel[5][5] = { {  0,  0,  0,  0,  0 },
//                                                  {  1,  1,  1,  1,  1 },
//                                                  {  0,  0,  0,  0,  0 },
//                                                  {  1,  1,  1,  1,  1 },
//                                                  {  0,  0,  0,  0,  0 } };
//                                                  
//         Frame im;
//         im.height = 5;
//         im.width = 5;
//         im.img[0] = 1;
//         im.img[1] = 1;
//         im.img[2] = 1;
//         im.img[3] = 1;
//         im.img[4] = 1;
//         im.img[5] = 1;
//         im.img[6] = 1;
//         im.img[7] = 1;
//         im.img[8] = 1;
//         im.img[9] = 1;
//         im.img[10] = 1;
//         im.img[11] = 1;
//         im.img[12] = 1;
//         im.img[13] = 1;
//         im.img[14] = 1;
//         im.img[15] = 1;
//         im.img[16] = 1;
//         im.img[17] = 1;
//         im.img[18] = 1;
//         im.img[19] = 1;
//         im.img[20] = 1;
//         im.img[21] = 1;
//         im.img[22] = 1;
//         im.img[23] = 1;
//         im.img[24] = 1;
//         add_images(&frame, &oframe);
//         
//         print_image(&frame);
//         Frame imm = convolve_image(&im, kernel);
//         print_image(&imm);
//         
//         return 0;
// }


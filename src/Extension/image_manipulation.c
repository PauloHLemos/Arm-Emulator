#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include "definitions.h"

uint8_t *get_pixel_ptr(frame *frame, int x, int y) {
        int index = x + y * frame->width;
        return (frame->img + index);
}

uint8_t get_pixel(frame *frame, int x, int y) {
        if (x < 0 || x >= frame->width || y < 0 || y >= frame->height) 
                return 0;
        return *get_pixel_ptr(frame, x, y);
}

void set_pixel(frame *frame, uint8_t value, int x, int y) {
        *get_pixel_ptr(frame, x, y) = value;
}

void add_images(frame *frame1, frame *frame2) {
        uint8_t new_value;
        for (int y = 0; y < frame1->height; y++) {
                for (int x = 0; x < frame1->width; x++) {
                        new_value = get_pixel(frame1, x, y) + get_pixel(frame2, x, y);
                        set_pixel(frame1, new_value, x, y);
                }
        }
}

void subtract_images(frame *frame1, frame *frame2) {
        uint8_t new_value;
        for (int y = 0; y < frame1->height; y++) {
                for (int x = 0; x < frame1->width; x++) {
                        new_value = get_pixel(frame1, x, y) - get_pixel(frame2, x, y);
                        set_pixel(frame1, new_value, x, y);
                }
        }
}

void multiply_image(frame *frame, float multiple) {
	uint8_t new_value;
	for (int y = 0; y < frame->height; y++) {
                for (int x = 0; x < frame->width; x++) {
                        new_value = round(get_pixel(frame, x, y) * multiple);
                        set_pixel(frame, new_value, x, y);
                }
        }
}

void lower_threshold_image(frame *frame, uint8_t threshold) {
        for (int y = 0; y < frame->height; y++) {
                for (int x = 0; x < frame->width; x++) {
                        if (get_pixel(frame, x, y) < threshold)
                                set_pixel(frame, 0, x, y);
                }
        }
}

void bitmask_image(frame *frame, frame *bitmask) {
        for (int y = 0; y < frame->height; y++) {
                for (int x = 0; x < frame->width; x++) {
                        if (get_pixel(bitmask, x, y) == 0)
                                set_pixel(frame, 0, x, y);
                }
        }
}

void print_image(frame *frame) {
        for (int y = 0; y < frame->height; y++) {
                for (int x = 0; x < frame->width; x++) {
                        printf("%d", get_pixel(frame, x, y));
                }
                printf("\n");
        }
}

frame rgb_to_greyscale(frame *frame) {
	frame grey;
	grey.width = frame->width;
	grey.height = frame->height;
	for (int i = 0; i < frame->width * frame->height; i++) {
		uint8_t average_colour = round((frame->img[3 * i] + frame->img[3 * i + 1] + frame->img[3 * i + 2]) / 3);
		grey.img[i] = average_colour;
    }
	return grey;
}

frame convolve_image(frame * frame, int kernel[5][5]) {
        uint8_t new_value;
        frame convolved_image;
        convolved_image.height = frame->height;
        convolved_image.width = frame->width;
        for (int y = 0; y < frame->height; y++) {
                for (int x = 0; x < frame->width; x++) {
                        new_value = 0;
                        for (int y_off = -2; y_off < 2; y_off++) {
                                for (int x_off = -2; x_off < 2; x_off++) {
                                        new_value += kernel[y_off][x_off] * get_pixel(frame, x + x_off, y + y_off);
                                }
                        }
                        set_pixel(&convolved_image, new_value, x, y);
                }
        }
        return convolved_image;
}

int main()
{
        printf("hello world");
        frame frame;
        frame.width = 2;
        frame.height = 2;
        frame.img = calloc(frame.width * frame.height, sizeof(uint8_t));
        frame.img[0] = 2;
        frame.img[1] = 4;
        frame.img[2] = 8;
        frame.img[3] = 9;
        
        frame oframe;
        oframe.width = 2;
        oframe.height = 2;
        oframe.img = calloc(frame.width * frame.height, sizeof(uint8_t));
        oframe.img[0] = 1;
        oframe.img[1] = 1;
        oframe.img[2] = 1;
        oframe.img[3] = 1;
        
        int kernel[5][5] = { {  0,  0,  0,  0,  0 },
                                                 {  1,  1,  1,  1,  1 },
                                                 {  0,  0,  0,  0,  0 },
                                                 {  1,  1,  1,  1,  1 },
                                                 {  0,  0,  0,  0,  0 } };
                                                 
        frame im;
        im.height = 5;
        im.width = 5;
        im.img[0] = 1;
        im.img[1] = 1;
        im.img[2] = 1;
        im.img[3] = 1;
        im.img[4] = 1;
        im.img[5] = 1;
        im.img[6] = 1;
        im.img[7] = 1;
        im.img[8] = 1;
        im.img[9] = 1;
        im.img[10] = 1;
        im.img[11] = 1;
        im.img[12] = 1;
        im.img[13] = 1;
        im.img[14] = 1;
        im.img[15] = 1;
        im.img[16] = 1;
        im.img[17] = 1;
        im.img[18] = 1;
        im.img[19] = 1;
        im.img[20] = 1;
        im.img[21] = 1;
        im.img[22] = 1;
        im.img[23] = 1;
        im.img[24] = 1;
        add_images(&frame, &oframe);
        
        print_image(&frame);
        frame imm = convolve_image(&im, kernel);
        print_image(&imm);
        
        return 0;
}


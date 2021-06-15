#include <stdio.h>
#include <stdint.h>
#include <math.h>

typedef struct greyscale_frame {
        int width;
        int height;
	int channels;
        uint8_t *frame;
} greyscale_frame;

typedef struct greyscale_frame {
        int width;
        int height;
	int channels;
        uint8_t *frame;
} frame;

uint8_t *get_pixel_ptr(greyscale_frame *frame, int x, int y) {
        int index = x + y * frame->width;
        return (frame->frame + index);
}

uint8_t get_pixel(greyscale_frame *frame, int x, int y) {
        if (x < 0 || x >= frame->width || y < 0 || y >= frame->height) 
                return 0;
        return *get_pixel_ptr(frame, x, y);
}

void set_pixel(greyscale_frame *frame, uint8_t value, int x, int y) {
        *get_pixel_ptr(frame, x, y) = value;
}

void add_images(greyscale_frame *frame1, greyscale_frame *frame2) {
        uint8_t new_value;
        for (int y = 0; y < frame1->height; y++) {
                for (int x = 0; x < frame1->width; x++) {
                        new_value = get_pixel(frame1, x, y) + get_pixel(frame2, x, y);
                        set_pixel(frame1, new_value, x, y);
                }
        }
}

void subtract_images(greyscale_frame *frame1, greyscale_frame *frame2) {
        uint8_t new_value;
        for (int y = 0; y < frame1->height; y++) {
                for (int x = 0; x < frame1->width; x++) {
                        new_value = get_pixel(frame1, x, y) - get_pixel(frame2, x, y);
                        set_pixel(frame1, new_value, x, y);
                }
        }
}

void multiply_image(greyscale_frame *frame, float multiple) {
	uint8_t new_value;
	for (int y = 0; y < frame1->height; y++) {
                for (int x = 0; x < frame1->width; x++) {
                        new_value = round(get_pixel(frame, x, y) * multiply);
                        set_pixel(frame, new_value, x, y);
                }
        }
}

void lower_threshold_image(greyscale_frame *frame, uint8_t threshold) {
        for (int y = 0; y < frame->height; y++) {
                for (int x = 0; x < frame->width; x++) {
                        if (get_pixel(frame, x, y) < threshold)
                                set_pixel(frame, 0, x, y);
                }
        }
}

void bitmask_image(greyscale_frame *frame, greyscale_frame *bitmask) {
        for (int y = 0; y < frame->height; y++) {
                for (int x = 0; x < frame->width; x++) {
                        if (get_pixel(bitmask, x, y) == 0)
                                set_pixel(frame, 0, x, y);
                }
        }
}

void print_image(greyscale_frame *frame) {
        for (int y = 0; y < frame->height; y++) {
                for (int x = 0; x < frame->width; x++) {
                        printf("%d", get_pixel(frame, x, y));
                }
                printf("\n");
        }
}

frame rgb_to_greyscale(frame *frame) {
	frame greyscale_frame;
	greyscale_frame.width = frame->width;
	greyscale_frame.height = frame->height;
	for (int i = 0; i < frame->width * frame_height; i++) {
		uint8_t average_colour = round((frame->frame[3 * i] + frame->frame[3 * i + 1] + frame->frame[3 * i + 2]) / 3);
		greyscale_frame[i] = average_colour;
        }
	return greyscale_frame;
}

greyscale_frame convolve_image(greyscale_frame * frame, int kernel[5][5]) {
        uint8_t new_value;
        greyscale_frame convolved_image;
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
        greyscale_frame frame;
        frame.width = 2;
        frame.height = 2;
        frame.frame[0] = 2;
        frame.frame[1] = 4;
        frame.frame[2] = 8;
        frame.frame[3] = 9;
        
        greyscale_frame oframe;
        oframe.width = 2;
        oframe.height = 2;
        oframe.frame[0] = 1;
        oframe.frame[1] = 1;
        oframe.frame[2] = 1;
        oframe.frame[3] = 1;
        
        int kernel[5][5] = { {  0,  0,  0,  0,  0 },
                                                 {  1,  1,  1,  1,  1 },
                                                 {  0,  0,  0,  0,  0 },
                                                 {  1,  1,  1,  1,  1 },
                                                 {  0,  0,  0,  0,  0 } };
                                                 
        greyscale_frame im;
        im.height = 5;
        im.width = 5;
        im.frame[0] = 1;
        im.frame[1] = 1;
        im.frame[2] = 1;
        im.frame[3] = 1;
        im.frame[4] = 1;
        im.frame[5] = 1;
        im.frame[6] = 1;
        im.frame[7] = 1;
        im.frame[8] = 1;
        im.frame[9] = 1;
        im.frame[10] = 1;
        im.frame[11] = 1;
        im.frame[12] = 1;
        im.frame[13] = 1;
        im.frame[14] = 1;
        im.frame[15] = 1;
        im.frame[16] = 1;
        im.frame[17] = 1;
        im.frame[18] = 1;
        im.frame[19] = 1;
        im.frame[20] = 1;
        im.frame[21] = 1;
        im.frame[22] = 1;
        im.frame[23] = 1;
        im.frame[24] = 1;
        add_images(&frame, &oframe);
        
        print_image(&frame);
        greyscale_frame imm = convolve_image(&im, kernel);
        print_image(&imm);
        
        return 0;
}



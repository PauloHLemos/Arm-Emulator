#include <stdlib.h>
#include <stdio.h>
#include "definitions.h"
#include "image_manipulation.h"
#include "generate_kernel.h"

double **blur7 = generate_blur(7);
double **blur9 = generate_blur(9);
double **laplacian = generate_laplace(3);

Frame *replace_background(Frame *frame_ptr, Frame *original_background_ptr, Frame *replacement_background_ptr) {
	Frame grey_frame = rgb_to_greyscale(frame_ptr);
	Frame *filtered_frame_ptr = filter_edges(&grey_frame);

	Frame grey_background = rgb_to_greyscale(original_background);
	Frame *filtered_background_ptr = filter_edges(&grey_background);

	absolute_difference(filtered_frame_ptr, filtered_background_ptr);
	
	Frame *bitmask = malloc(sizeof(Frame));
	bitmask_ptr->frame = calloc(frame_ptr->height * frame_ptr->width, sizeof(uint8_t));
	bitmask_ptr->height = frame_ptr->height;
	bitmask_ptr->width = frame_ptr->width;
	bitmask_ptr->num_channels = 1;
	
	fill_left(filtered_frame_ptr, bitmask_ptr, 127);
	fill_right(filtered_frame_ptr, bitmask_ptr, 127);
	
	add_image_with_bitmask(frame_ptr, replacement_background_ptr, bitmask_ptr);

	return frame_ptr
}
	
Frame *filter_edges(Frame *frame_ptr) {
	Frame *filtered_frame_ptr = malloc(sizeof(Frame));
	*filtered_frame_ptr = convolve_image(frame_ptr, 7, *blur7);
	*filtered_frame_ptr = convolve_image(&filtered_frame_ptr, 3, *laplacian);
	*filtered_frame_ptr = convolve_image(&filtered_frame_ptr, 9, *blur9);
	return filtered_frame_ptr;
}

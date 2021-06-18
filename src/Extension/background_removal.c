#include <stdlib.h>
#include <stdio.h>
#include "definitions.h"
#include "image_manipulation.h"
#include "generate_kernel.h"

Frame *filter_edges(Frame *frame_ptr);

Frame *replace_background(Frame *frame_ptr, Frame *original_background_ptr, Frame *replacement_background_ptr) {
	Frame grey_frame = rgb_to_greyscale(frame_ptr);
	Frame *filtered_frame_ptr = filter_edges(&grey_frame);

	Frame grey_background = rgb_to_greyscale(original_background_ptr);
	Frame *filtered_background_ptr = filter_edges(&grey_background);
	absolute_difference(filtered_frame_ptr, filtered_background_ptr);
	

	Frame *bitmask_ptr = malloc(sizeof(Frame));
	bitmask_ptr->img = calloc(frame_ptr->height * frame_ptr->width, sizeof(uint8_t));
	bitmask_ptr->height = frame_ptr->height;
	bitmask_ptr->width = frame_ptr->width;
	bitmask_ptr->num_channels = 1;

	
	fill_left(filtered_frame_ptr, bitmask_ptr, 127);
	fill_right(filtered_frame_ptr, bitmask_ptr, 127);
	
	bitmask_image(replacement_background_ptr, bitmask_ptr);
	invert_bitmask(bitmask_ptr);
	bitmask_image(replacement_background_ptr, bitmask_ptr);
	add_images(frame_ptr, replacement_background_ptr);

	return frame_ptr;
}
	
Frame *filter_edges(Frame *frame_ptr) {
	double **blur7 = generate_blur(7);
	double **blur9 = generate_blur(9);
	double **laplacian = generate_laplace(3);

//	Frame *blur7_frame_ptr = malloc(sizeof(Frame));
//	Frame *laplacian_frame_ptr = malloc(sizeof(Frame));
//	Frame *blur9_frame_ptr = malloc(sizeof(Frame));
//	*blur7_frame_ptr = convolve_image(frame_ptr, 7, *blur7);
//	Frame blur7_frame_ptr = convolve_image(frame_ptr, 7, *blur7);
	// *laplacian_frame_ptr = 

	Frame blur7_frame = convolve_image(frame_ptr, 7, blur7);
	Frame laplacian_frame  = convolve_image(&blur7_frame, 3, laplacian);
	Frame *blur9_frame_ptr = malloc(sizeof(Frame));
	 *blur9_frame_ptr = convolve_image(&laplacian_frame, 9, blur9);
	
	return blur9_frame_ptr;
}

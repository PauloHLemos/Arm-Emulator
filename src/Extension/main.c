
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "definitions.h"
#include "utils.h"
#include "image_storer.h"
#include "image_loader.h"
#include "image_manipulation.h"
#include "generate_kernel.h"
#include "video_processor.h"
#include "background_removal.h"

uint8_t *detect_edges(Frame_Buffer* fb_ptr) {
        double laplacian[][3] = { {  0,  -1,  0 },
				  {  -1,  4,  -1 },
       			      	  {  0,  -1,  0 } };
	assert(fb_ptr->buffer_size == 1);
	double **blur = generate_blur(5);

	Frame current_frame;
	current_frame.width	   = fb_ptr->width;
	current_frame.height	   = fb_ptr->height;
	current_frame.num_channels = fb_ptr->num_channels;
	current_frame.img	   = fb_ptr->buffer[fb_ptr->index];

	// Frame grayscale_image	   = rgb_to_greyscale(&current_frame);
	rgb_to_greyscale_direct(&current_frame);
	//convolve_image_direct(&current_frame, 5, blur);
	convolve_image_direct(&current_frame, 3, laplacian);
	// convolve_image_direct(&current_frame, 5, blur);
	// Frame grayscale_image_blur = convolve_image(&current_frame, 5, blur);
	// Frame convolved_image	   = convolve_image(&grayscale_image_blur, 3, laplacian);
	// Frame convolved_image_blur = convolve_image(&convolved_image, 5, blur);

	// // store_image(&convolved_image_blur, "test_out.png");

	// deallocate_kernel(blur, 5);
	// // deallocate_frame(frame_ptr); must be freed elsewhere
	// // deallocate_img(&grayscale_image);
	// deallocate_img(&grayscale_image_blur);
	// deallocate_img(&convolved_image);
	// // deallocate_img(&convolved_image_blur); must be freed elsewhere

	// one_to_three_channels(&convolved_image_blur);
	one_to_three_channels(&current_frame);
	return current_frame.img;
}

int main(void) {
	Frame *original_background_ptr = load_image("samples/FMmY6.png", 3);
	Frame *desired_background_ptr = load_image("samples/FMmY6.png", 3);
	Frame *current_frame_ptr = load_image("samples/FMmY6.png", 3);
		
	Frame *processed_frame_ptr = replace_background(current_frame_ptr, original_background_ptr, desired_background_ptr);		
	// double **blur = generate_blur(5);

	// Frame grayscale_image	   = rgb_to_greyscale(frame_ptr);
	// Frame grayscale_image_blur = convolve_image(&grayscale_image, 5, blur);
	// Frame convolved_image	   = convolve_image(&grayscale_image_blur, 3, laplacian);
	// Frame convolved_image_blur = convolve_image(&convolved_image, 5, blur);
	// one_to_three_channels(&convolved_image_blur);

	// store_image(&convolved_image_blur, "test_out.png");

	// deallocate_kernel(blur, 5);
	// deallocate_frame(frame_ptr);
	// deallocate_img(&grayscale_image);
	// deallocate_img(&grayscale_image_blur);
	// deallocate_img(&convolved_image);
	// deallocate_img(&convolved_image_blur);

 	// process_video("samples/teapot.mp4", "samples/test_output.mp4", 1, *detect_edges);	
	
	return 0;
}

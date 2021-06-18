
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

int main(void) {
	Frame *original_background_ptr = load_image("samples/original_background.png", 3);
	Frame *desired_background_ptr = load_image("samples/desired_background.png", 3);
	Frame *current_frame_ptr = load_image("samples/current_frame.png", 3);
		
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
	
	store_image(processed_frame_ptr, "samples/background_replacement.png");

	
	Frame *right_side = load_image("samples/right_side.png", 3);
	Frame *left_side = load_image("samples/left_side.png", 3);

	add_images(right_side, left_side);

	store_image(right_side, "added_images.png");

	return 0;
}

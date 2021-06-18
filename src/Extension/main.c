
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
	
	store_image(processed_framdddd_ptr, "samples/background_replacement.png");

	
	Frame *baboon_ptr = load_image("samples/baboon.png", 3);
	Frame *aeroplane_ptr = load_image("samples/aeroplane.png", 3);
	
	Frame *gray_baboon_ptr = rgb_to_greyscale(baboon_ptr);
	Frame *gray_aeroplane_ptr = rgb_to_greyscale(aeroplane_ptr);	

	add_images(gray_baboon_ptr, gray_aeroplane_ptr);
	one_to_three_channels(grey_baboon_ptr);

	store_image(grey_baboon_ptr, "addition.png");

	return 0;
}

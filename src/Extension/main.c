
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

Frame blur(Frame_Buffer frame_buffer) {
	Frame *frame = frame_buffer.buffer[0];
	double **blur = generate_blur(5);	
	return convolve_image(frame, 5, blur);
}
	

int main(void) {
	Frame *original_background_ptr = load_image("samples/original_background.png", 3);
	Frame *desired_background_ptr = load_image("samples/desired_background.png", 3);
	Frame *current_frame_ptr = load_image("samples/current_frame.png", 3);
		
	Frame *processed_frame_ptr = replace_background(current_frame_ptr, original_background_ptr, desired_background_ptr);		
	store_image(processed_frame_ptr, "samples/background_replacement.png");

	
	Frame *baboon_ptr = load_image("samples/baboon.png", 3);
	Frame *aeroplane_ptr = load_image("samples/aeroplane.png", 3);
	
	Frame *gray_baboon_ptr = rgb_to_greyscale(baboon_ptr);
	Frame *gray_aeroplane_ptr = rgb_to_greyscale(aeroplane_ptr);	

	add_images(gray_baboon_ptr, gray_aeroplane_ptr);
	one_to_three_channels(grey_baboon_ptr);

	store_image(grey_baboon_ptr, "addition.png");

	
	double **laplacian = generate_laplace(3);
	Frame aeroplane_edges = convolve_image(gray_aeroplane_ptr, 3, laplacian);
	one_to_three_channels(&aeroplane_edges);
	
	store_image(&aeroplane_edges, "edges.png");


	process_video("samples/Venice_10.mp4", "samples/blurred_venice.mp4", 1, blur);
	

	return 0;
}

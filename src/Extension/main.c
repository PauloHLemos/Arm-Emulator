
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "image_storer.h"
#include "image_loader.h"
#include "image_manipulation.h"
#include "generate_kernel.h"

int main(void) {
       double kernel[][5] = { {  1,  0,  1,  0,  1 },
			    {  0,  1,  0,  1,  0 },
       			    {  1,  0,  1,  0,  1 },
       			    {  0,  1,  0,  1,  0 },
       			    {  1,  0,  1,  0,  1 } };
       double sobel_x[][3] = { {  -1,  0,  1 },
			       {  -2,  0,  2 },
       			       {  -1,  0,  1 } };
       double sobel_y[][3] = { {  -1,  -2,  -1 },
			       {  0,  0,  0 },
       			       {  1,  2,  1 } };
       double laplacian[][3] = { {  0,  -1,  0 },
				 {  -1,  4,  -1 },
       			      	 {  0,  -1,  0 } };
       double blur[][5] = { {  0.008,  0.008,  0.008,  0.008,  0.008 },
			    {  0.008,  0.008,  0.008,  0.008,  0.008 },
       			    {  0.008,  0.008,  0.008,  0.008,  0.008 },
       			    {  0.008,  0.008,  0.008,  0.008,  0.008 },
       			    {  0.008,  0.008,  0.008,  0.008,  0.008 } };
       double weak_blur[][3] = { {  0.1,  0.1,  0.1 },
       			    	 {  0.1,  0.1,  0.1 },
       			    	 {  0.1,  0.1,  0.1 } };
	Frame *frame_ptr = load_image("samples/FMmY6.png", 3);

	double **blur_test = generate_blur(5);

	Frame grayscale_image	   = rgb_to_greyscale(frame_ptr);
	Frame grayscale_image_blur = convolve_image(&grayscale_image, 5, blur);
	Frame convolved_image	   = convolve_image(&grayscale_image_blur, 3, laplacian);
	Frame convolved_image_blur = convolve_image(&convolved_image, 5, blur_test);

	store_image(&convolved_image_blur, "test_out.png");

	deallocate_kernel(blur_test, 5);
	deallocate_frame(frame_ptr);
	deallocate_img(&grayscale_image);
	deallocate_img(&grayscale_image_blur);
	deallocate_img(&convolved_image);
	deallocate_img(&convolved_image_blur);
	return 0;
}

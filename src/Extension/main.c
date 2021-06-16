
#include <stdio.h>
#include "utils.h"
#include "image_storer.h"
#include "image_loader.h"
#include "image_manipulation.h"

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
       double blur[][3] = { {  1,  1,  1 },
			  {  1,  1,  1 },
       			  {  1,  1,  1 } };
       double laplacian[][3] = { {  0,  -1,  0 },
				 {  -1,  4,  -1 },
       			      	 {  0,  -1,  0 } };
	Frame *frame_ptr = load_image("samples/FMmY6.png", 3);
	Frame grayscale_image = rgb_to_greyscale(frame_ptr);
	Frame convolved_image = convolve_image(&grayscale_image, 3, laplacian);
	// Frame convolved_image_y = convolve_image(&convolved_image_x, 3, sobel_y);
	store_image(&convolved_image, "test_out.png");
	//deallocate_frame(&greyscale_frame);
	deallocate_frame(frame_ptr);
	return 0;
}

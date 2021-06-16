
#include <stdio.h>
#include "utils.h"
#include "image_storer.h"
#include "image_loader.h"
#include "image_manipulation.h"

int main(void) {
       int kernel[5][5] = { {  1,  0,  1,  0,  1 },
			    {  0,  1,  0,  1,  0 },
       			    {  1,  0,  1,  0,  1 },
       			    {  0,  1,  0,  1,  0 },
       			    {  1,  0,  1,  0,  1 } };
	Frame *frame_ptr = load_image("samples/aeroplane.png", 3);
	Frame convolved_image = convolve_image(frame_ptr, kernel);
	store_image(&convolved_image, "test_out.png");
	//deallocate_frame(&greyscale_frame);
	deallocate_frame(frame_ptr);
	return 0;
}

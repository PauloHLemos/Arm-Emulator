
#include <stdio.h>
#include "utils.h"
#include "image_storer.h"
#include "image_loader.h"
#include "image_manipulation.h"

int main(void) {
       int kernel[][5] = { {  1,  0,  1,  0,  1 },
			    {  0,  1,  0,  1,  0 },
       			    {  1,  0,  1,  0,  1 },
       			    {  0,  1,  0,  1,  0 },
       			    {  1,  0,  1,  0,  1 } };
       int sobel[][3] = { {  -1,  0,  1 },
			  {  -2,  0,  2 },
       			  {  -1,  0,  1 } };
       int blur[][3] = { {  1,  1,  1 },
			  {  1,  1,  1 },
       			  {  1,  1,  1 } };
	Frame *frame_ptr = load_image("samples/oldestmanthumb.jpg", 3);
	Frame convolved_image = convolve_image(frame_ptr, 3, sobel);
	store_image(frame_ptr, "test_out.png");
	//deallocate_frame(&greyscale_frame);
	deallocate_frame(frame_ptr);
	return 0;
}

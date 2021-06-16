
#include <stdio.h>
#include "utils.h"
#include "image_storer.h"
#include "image_loader.h"
#include "image_manipulation.h"

int main(void) {
	Frame *frame_ptr = load_image("samples/aeroplane.png", 3);
	Frame greyscale_frame = rgb_to_greyscale(frame_ptr);
	store_image(&greyscale_frame, "test_out.png");
	//deallocate_frame(&greyscale_frame);
	deallocate_frame(frame_ptr);
	return 0;
}

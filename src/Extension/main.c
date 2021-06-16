
#include <stdio.h>
#include "utils.h"
#include "image_storer.h"
#include "image_loader.h"
#include "image_manipulation.h"

int main(void) {
	Frame *frame_ptr = load_image("samples/aeroplane.png", 3);
	store_image(frame_ptr, "test_out.jpeg");
	deallocate_frame(frame_ptr);
	return 0;
}

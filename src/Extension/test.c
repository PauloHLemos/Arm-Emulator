#include <stdio.h>
#include "utils.h"
#include "image_loader.h"
#include "image_storer.h"
#include "definitions.h"
#include "utils.h"

 int main(void) {
	FRAME *frame_ptr = load_image("samples/aeroplane.png", 3);
        printf("width: %d, height %d, num_channel:s %d, size of arr: %ld.\n", frame_ptr->width, frame_ptr->height,
                frame_ptr->num_channels, sizeof(frame_ptr->img));
	store_image(frame_ptr, "test_out.jpeg");
	deallocate_frame(frame_ptr);
        return 0;
}

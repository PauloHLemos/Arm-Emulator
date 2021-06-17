#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include "definitions.h"

void deallocate_frame(Frame *frame_ptr);
void deallocate_img(Frame *frame_ptr);
uint8_t *avg_arrays(uint8_t* arr1, uint8_t* arr2);

#endif

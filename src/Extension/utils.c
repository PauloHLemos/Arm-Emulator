#include <stdlib.h>
#include <assert.h>
#include "utils.h"

void deallocate_frame(FRAME *frame_ptr) {
	free(frame_ptr->img);
	free(frame_ptr);
}

uint8_t *avg_arrays(uint8_t* arr1, uint8_t* arr2) {
	assert(sizeof(arr1) == sizeof(arr2));
	uint8_t *res = malloc(sizeof(arr1));
	for (int i = 0; i < (sizeof(arr1) / sizeof(uint8_t)); i++) {
		*res = *arr1 + *arr2;
		res++;
		arr1++;
		arr2++;
	}
	return res;
}

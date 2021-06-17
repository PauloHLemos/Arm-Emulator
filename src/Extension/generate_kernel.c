#include "generate_kernel.h"
#include <stdlib.h>


double **generate_blur(int size) {
	double **spine_ptr = malloc(size * sizeof(double *));

	for (int i = 0; i < size; i++) {
		spine_ptr[i] = malloc(size * sizeof(double));
		for (int j = 0; j < size; j++) {
			spine_ptr[i][j] = (double) 1 / (size * size);
		}
	}

	return spine_ptr; 
}

double **generate_laplace(int size) {
	return 0;
}

void deallocate_kernel(double **kernel_ptr, int size) {
	for (int i = 0; i < size; i++) free(kernel_ptr[i]);
	free(kernel_ptr);
}

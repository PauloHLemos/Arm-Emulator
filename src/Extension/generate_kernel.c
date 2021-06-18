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
	double **laplace_ptr = malloc(size * sizeof(double *));
	
	for (int i = 0; i < size; i++) {
		laplace_ptr[i] = malloc(size * sizeof(double));
	}

	laplace_ptr[0][0] = 0;
	laplace_ptr[0][1] = 0;
	laplace_ptr[0][2] = 0;
	laplace_ptr[1][0] = 0;
	laplace_ptr[1][1] = 0;
	laplace_ptr[1][2] = 0;
	laplace_ptr[2][0] = 0;
	laplace_ptr[2][1] = 0;
	laplace_ptr[2][2] = 0;

	return laplace_ptr;
}

void deallocate_kernel(double **kernel_ptr, int size) {
	for (int i = 0; i < size; i++) free(kernel_ptr[i]);
	free(kernel_ptr);
}

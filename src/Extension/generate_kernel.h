#ifndef GENERATE_KERNEL_H
#define GENERATE_KERNEL_H


double **generate_blur(int size);

double **generate_laplace(int size);

void deallocate_kernel(double **kernel_ptr, int size);


#endif

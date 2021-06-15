#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdint.h>

typedef struct {
	int width;
	int height;
	int num_channels;
	uint8_t *img;
} FRAME;

#endif

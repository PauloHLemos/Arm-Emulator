#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdint.h>

struct Frame {
	int width;
	int height;
	int num_channels;
	uint8_t *img;
};

#endif

#ifndef DECODE_H
#define DECODE_H

#include <stdint.h>
#include "definitions.h"

struct Instruction decode(uint32_t instruction_binary);

#endif

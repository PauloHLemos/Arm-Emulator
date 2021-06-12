#ifndef SHIFTS_H
#define SHIFTS_H

#include <stdint.h>
#include <stdbool.h>
#include "definitions.h"

uint32_t logical_shift_left(uint32_t n, uint32_t spaces, bool *carry_flag_ptr); 
uint32_t logical_shift_right(uint32_t n, uint32_t spaces, bool *carry_flag_ptr);
uint32_t arithmetic_shift_right(uint32_t n, uint32_t spaces, bool *carry_flag_ptr);
uint32_t rotate_right(uint32_t n, uint32_t spaces, bool *carry_flag_ptr);
uint32_t rotate_left(uint32_t n, uint32_t spaces, bool *carry_flag_ptr);

#endif

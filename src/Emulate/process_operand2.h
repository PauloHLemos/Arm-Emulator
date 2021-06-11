#ifndef PROCESS_OPERAND2_H
#define PROCESS_OPERAND2_H

#include <stdint.h>
#include <stdbool.h>
#include "definitions.h"

uint32_t process_operand2_immediate_value(uint32_t operand2, bool *carry_flag_ptr); 
uint32_t process_operand2_shifted_register(struct State *state_ptr, uint32_t operand2, bool *carry_flag_ptr);
uint32_t get_shift_amount(struct State *state_ptr, uint32_t operand2);
uint32_t shift(uint32_t rm, uint32_t shift_code, uint32_t shift_amount, bool *carry_flag_ptr);
uint32_t logical_shift_left(uint32_t n, uint32_t spaces, bool *carry_flag_ptr); 
uint32_t logical_shift_right(uint32_t n, uint32_t spaces, bool *carry_flag_ptr);
uint32_t arithmetic_shift_right(uint32_t n, uint32_t spaces, bool *carry_flag_ptr);
uint32_t rotate_right(uint32_t n, uint32_t spaces, bool *carry_flag_ptr);

#endif

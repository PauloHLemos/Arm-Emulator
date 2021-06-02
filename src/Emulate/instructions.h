#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include <stdbool.h>
#include <stdint.h>
#include "definitions.h"

void data_processing(struct State *state_ptr, struct Instruction *instruction_ptr);
void multiply(struct State *state_ptr, struct Instruction *instruction_ptr);
void single_data_transfer(struct State *state_ptr, struct Instruction *instruction_ptr);
void branch(struct State *state_ptr, struct Instruction *instruction_ptr);

#endif

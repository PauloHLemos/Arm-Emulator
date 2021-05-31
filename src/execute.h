#ifndef EXECUTE_H
#define EXECUTE_H

#include <stdbool.h>
#include "definitions.h"

bool execute(struct Instruction *instruction, struct State *state_ptr);

#endif

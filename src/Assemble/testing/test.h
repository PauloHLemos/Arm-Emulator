#ifndef TEST_H
#define TEST_H

#include <stdbool.h>
#include <stdint.h>

bool assert_true(bool condition, char *error_message);
bool assert_int_equals(uint32_t value, uint32_t expected, char *error_message);

#endif

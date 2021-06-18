#ifndef PROCESS_OPERAND2_H
#define PROCESS_OPERAND2_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "process_operand2.h"
#include "shifts.h"

uint32_t find_rotation(uint32_t operand) {
	assert(operand >= (1 << 8));
	uint32_t shifted = operand;
	bool carry;
	for (int i = 0; i < 16; i++, shifted = rotate_left(shifted, 2, &carry)) {
		if ((shifted & 0xff) == shifted) {
			return (i << 8) + shifted;
		}
	}
	fprintf(stderr, "Error: Number %d cannot be represented as an immediate operand. ", operand);
	exit(1);
}

uint32_t process_operand2_shifted_register(char *operand2_string) {
	char shift_register_string[10] = "";
	uint32_t operand2 = 0;

	for ( ; *operand2_string != ',' && *operand2_string != '\0'; operand2_string += 1) 
			strncat(shift_register_string, operand2_string, 1);
	
	// register no shift case
	operand2 += atoi(shift_register_string + 1);
	if (*operand2_string == '\0') return operand2;

	char shift_type_string[10] = "";
	char shift_amount_string[20] = "";
	operand2_string += (*(operand2_string + 1) == ' ') ? 2 : 1;
	for ( ; *operand2_string != ' '; operand2_string += 1) 
			strncat(shift_type_string, operand2_string, 1);
	operand2_string += 1;
	for ( ; *operand2_string != '\0'; operand2_string += 1) 
			strncat(shift_amount_string, operand2_string, 1);
	

	// cases on next letter of shift_amount_string
	if	(strcmp(shift_type_string, "lsl") == 0)	{  }
	else if (strcmp(shift_type_string, "lsr") == 0) { operand2 += (1 << 5); }
	else if (strcmp(shift_type_string, "asr") == 0) { operand2 += (2 << 5); }
	else if (strcmp(shift_type_string, "ror") == 0) { operand2 += (3 << 5); }

	if (*shift_amount_string == 'r') {
		operand2 += (1 << 4); // signifies is a shifted reg
		uint32_t shift_register = strtol(shift_amount_string + 1, NULL, 0);
		assert(shift_register < (1 << 4));
		operand2 += (shift_register << 8);

	} else if (*shift_amount_string == '#') {
		uint32_t immediate_shift = strtol(shift_amount_string + 1, NULL, 0);
		assert(immediate_shift < (1 << 5));
		operand2 += (immediate_shift << 7);
	}

	return operand2;
}

void process_operand2(char *operand2_string, uint32_t *operand2_ptr, bool *immediate_operand_ptr) {
	if (*operand2_string == '#') {
		*immediate_operand_ptr = true;
		operand2_string += 1;
		uint32_t result = (uint32_t) strtol(operand2_string, NULL, 0); 
		*operand2_ptr = (result >= (1 << 8)) ? find_rotation(result) : result;
	} else {
		*immediate_operand_ptr = false;
		*operand2_ptr = process_operand2_shifted_register(operand2_string);
	}
}


#endif

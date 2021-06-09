#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "definitions.h"
#include "test.h"
#include "split_instructions.h"
#include "test_translate_data_processing.h"
#include "shifts.h"
// #include "instructions.h"

void convert_opcode(char *opcode_string, enum Opcode *opcode_ptr, enum Condition *cond_ptr) {
	if (strcmp(opcode_string, "andeq") == 0) {
		*opcode_ptr = AND;
		*cond_ptr = EQUAL;
		return;
	}
	*cond_ptr = ALWAYS;

	if	(strcmp(opcode_string, "and") == 0) { *opcode_ptr = AND; } 
	else if (strcmp(opcode_string, "eor") == 0) { *opcode_ptr = EXCLUSIVE_OR; }
	else if (strcmp(opcode_string, "sub") == 0) { *opcode_ptr = SUBTRACT; }
	else if (strcmp(opcode_string, "rsb") == 0) { *opcode_ptr = REVERSE_SUBTRACT; }
	else if (strcmp(opcode_string, "add") == 0) { *opcode_ptr = ADD; }
	else if (strcmp(opcode_string, "orr") == 0) { *opcode_ptr = OR; }
	else if (strcmp(opcode_string, "mov") == 0) { *opcode_ptr = MOVE; }
	else if (strcmp(opcode_string, "tst") == 0) { *opcode_ptr = TEST_BITS; }
	else if (strcmp(opcode_string, "teq") == 0) { *opcode_ptr = TEST_EQUALS; }
	else if (strcmp(opcode_string, "cmp") == 0) { *opcode_ptr = COMPARE; }
	else { fprintf(stderr, "Opcode \"%s\" does not exist. \n", opcode_string); exit(1); }
}
bool instruction_computes_results(enum Opcode opcode) {
	switch(opcode) {
		case AND:	       return true;
		case EXCLUSIVE_OR:     return true;
		case SUBTRACT:	       return true;
		case REVERSE_SUBTRACT: return true;
		case ADD:	       return true;
		case OR:	       return true;
		default:	       return false;
	}
}

bool instruction_sets_CPSR_only(enum Opcode opcode) {
	switch(opcode) {
		case TEST_BITS:	  return true;
		case TEST_EQUALS: return true;
		case COMPARE:	  return true;
		default:	  return false;
	}
}

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
	exit(0);
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
		uint32_t shift_register = atoi(shift_amount_string + 1);
		assert(shift_register < (1 << 4));
		operand2 += (shift_register << 8);

	} else if (*shift_amount_string == '#') {
		uint32_t immediate_shift = atoi(shift_amount_string + 1);
		assert(immediate_shift < (1 << 5));
		operand2 += (immediate_shift << 7);
	}

	return operand2;
}

void process_operand2(char *operand2_string, uint32_t *operand2_ptr, bool *immediate_operand_ptr) {
	if (*operand2_string == '#') {
		*immediate_operand_ptr = true;
		operand2_string += 1;
		// TODO: fix incomplete behaviour, what if there is an overflow
		uint32_t result = (uint32_t) strtol(operand2_string, NULL, 0); 
		*operand2_ptr = (result >= (1 << 8)) ? find_rotation(result) : result;

	} else {
		*immediate_operand_ptr = false;
		*operand2_ptr = process_operand2_shifted_register(operand2_string);
	}
}


struct Instruction translate_data_processing(char *instruction, struct ST_Node *st_head_ptr) {
	struct Instruction instruction_struct;
	
	char opcode_string[100];
	extract_opcode(instruction, opcode_string);
	convert_opcode(opcode_string, &instruction_struct.opcode, &instruction_struct.cond);

	char operand2_string[100];
	if (instruction_computes_results(instruction_struct.opcode))  {
		// Result computing instructions AND, EOR, SUB, RSB, ADD, ORR
		char rd[100];
		char rn[100];
		split_4_arguments(instruction, opcode_string, rd, rn, operand2_string);

		instruction_struct.rd = *(rd + 1) - '0';
		instruction_struct.rn = *(rn + 1) - '0';
		instruction_struct.set_condition_codes = false;
	} else if (instruction_struct.opcode == MOVE)  {
		// MOV instruction
		char rd[100];
		split_3_arguments(instruction, opcode_string, rd, operand2_string);

		instruction_struct.rd = *(rd + 1) - '0';
		instruction_struct.set_condition_codes = false;
	} else if (instruction_sets_CPSR_only(instruction_struct.opcode)) {
		// CPSR setting instructions
		char rn[100];
		split_3_arguments(instruction, opcode_string, rn, operand2_string);

		instruction_struct.rn = *(rn + 1) - '0';
		instruction_struct.set_condition_codes = true;
	} 

	uint32_t operand2;
	bool immediate_operand;
	process_operand2(operand2_string, &operand2, &immediate_operand);

	instruction_struct.immediate_operand = immediate_operand;
	instruction_struct.operand2	     = operand2;

	return instruction_struct;
}

int main(void) {
	run_tests();
	return 0;
}


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "definitions.h"
#include "split_instructions.h"
#include "shifts.h"
#include "process_operand2.h"
#include "instructions.h"

void set_opcode_cond(char *opcode_string, enum Opcode *opcode_ptr, enum Condition *cond_ptr) {
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

void process_result_computing_instruction(char *instruction_string,
					  uint8_t *rd_ptr,
				       	  uint8_t *rn_ptr,
				       	  bool *set_condition_codes_ptr,
				       	  bool *immediate_operand_ptr,
				       	  uint32_t *operand2_ptr) {

		char rd[100], rn[100], operand2_string[100];
		split_3_arguments_after_opcode(instruction_string, rd, rn, operand2_string);

		*rd_ptr			 = atoi(rd + 1);
		*rn_ptr 		 = atoi(rn + 1);
		*set_condition_codes_ptr = false;

		process_operand2(operand2_string, operand2_ptr, immediate_operand_ptr);
}

void process_move_instruction(char *instruction_string,
			      uint8_t *rd_ptr,
		       	      bool *set_condition_codes_ptr,
		       	      bool *immediate_operand_ptr,
		       	      uint32_t *operand2_ptr) {
		char rd[100], operand2_string[100];
		split_2_arguments_after_opcode(instruction_string, rd, operand2_string);

		*rd_ptr			 = atoi(rd + 1);
		*set_condition_codes_ptr = false;

		process_operand2(operand2_string, operand2_ptr, immediate_operand_ptr);
}

void process_cpsr_instruction(char *instruction_string,
			      uint8_t *rn_ptr,
		       	      bool *set_condition_codes_ptr,
		       	      bool *immediate_operand_ptr,
		       	      uint32_t *operand2_ptr) {
		char rn[100], operand2_string[100];
		split_2_arguments_after_opcode(instruction_string, rn, operand2_string);

		*rn_ptr			 = atoi(rn + 1);
		*set_condition_codes_ptr = true;

		process_operand2(operand2_string, operand2_ptr, immediate_operand_ptr);
}

void process_instruction(char *instruction_string,
			 enum Opcode opcode,
			 uint8_t *rd_ptr,
			 uint8_t *rn_ptr,
		       	 bool *set_condition_codes_ptr,
			 bool *immediate_operand_ptr,
			 uint32_t *operand2_ptr) {
	if (instruction_computes_results(opcode))  { 
		process_result_computing_instruction(instruction_string,
						     rd_ptr,
			      	  		     rn_ptr,
			      	  		     set_condition_codes_ptr,
			      	  		     immediate_operand_ptr,
			      	  		     operand2_ptr);
	} else if (opcode == MOVE)  {				 
		process_move_instruction(instruction_string,
					 rd_ptr,
			  		 set_condition_codes_ptr,
			  		 immediate_operand_ptr,
		  	  		 operand2_ptr); 
	} else if (instruction_sets_CPSR_only(opcode)) {		 
		process_cpsr_instruction(instruction_string,
					 rn_ptr,
					 set_condition_codes_ptr,
					 immediate_operand_ptr,
					 operand2_ptr); 
	} 
}

struct Instruction translate_data_processing(char *instruction_string) {
	struct Instruction instruction_struct;
	memset(&instruction_struct, 0, sizeof(struct Instruction));
	
	instruction_struct.type = DATA_PROCESSING;

	char opcode_string[10];
	extract_opcode(instruction_string, opcode_string);
	if (strcmp(opcode_string, "andeq") == 0) return instruction_struct;
	if (strcmp(opcode_string, "lsl") == 0) {
		char rn[10], expression[30], new_instruction_string[100];
		split_2_arguments_after_opcode(instruction_string, rn, expression);
		snprintf(new_instruction_string, 100, "mov %s, %s, lsl %s", rn, rn, expression);

		instruction_string = new_instruction_string;
		memcpy(opcode_string, "mov", 4);
	}

	set_opcode_cond(opcode_string, 
			&instruction_struct.opcode, 
			&instruction_struct.cond);

	process_instruction(instruction_string,
			    instruction_struct.opcode,
			    &instruction_struct.rd,
			    &instruction_struct.rn,
			    &instruction_struct.set_condition_codes,
			    &instruction_struct.immediate_operand,
			    &instruction_struct.operand2);


	return instruction_struct;
}

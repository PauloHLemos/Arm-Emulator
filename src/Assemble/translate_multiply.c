#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "split_instructions.h"
#include "instructions.h"
#include "definitions.h"

struct Instruction translate_multiply(char *instruction) {
       struct Instruction instruction_struct;
       char opcode[100], rd[100], rm[100], rs[100], rn[100];
       instruction_struct.type = MULTIPLY;
       instruction_struct.cond = ALWAYS;
       extract_opcode(instruction, opcode);
       if (strcmp(opcode, "mla") == 0) {
	       split_4_arguments_after_opcode(instruction, rd, rm, rs, rn);
	       instruction_struct.rn = atoi(rn + 1);
	       instruction_struct.accumulate = true;
       } else {
	       split_3_arguments_after_opcode(instruction, rd, rm, rs);
	       instruction_struct.accumulate = false;
       }
       instruction_struct.rd = atoi(rd + 1);
       instruction_struct.rm = atoi(rm + 1);
       instruction_struct.rs = atoi(rs + 1);
       instruction_struct.set_condition_codes = false;
       return instruction_struct;
}

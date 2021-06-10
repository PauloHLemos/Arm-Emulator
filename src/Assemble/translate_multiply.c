#include <stdint.h>
#include <stdbool.h>
#include "split_instructions.h"
#include "instructions.h"
#include "definitions.h"

struct Instruction translate_multiply(char *instruction) {
       struct Instruction instruction_struct;
       char opcode[4], rd[4], rm[4], rs[4], rn[4];
       instruction_struct.type = MULTIPLY;
       instruction_struct.cond = ALWAYS;
       extract_opcode(instruction, opcode);
       if (opcode == "mla") {
	       split_4_arguments(instruction, rd, rm, rs, rn);
	       instruction_struct.rn = atoi(rn + 1);
	       instruction_struct.accumulate = true;
       } else {
	       split_3_arguments(instruction, rd, rm, rs);
	       instruction_struct.accumulate = false;
       }
       instruction_struct.rd = atoi(rd + 1);
       instruction_struct.rm = atoi(rm + 1);
       instruction_struct.rs = atoi(rs + 1);
       instruction_struct.set_condition_codes = false;
       return instruction_struct;
}

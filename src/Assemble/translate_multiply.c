#include <stdint.h>
#include <stdbool.h>
#include "split_instructions.h"
#include "instructions.h"
#include "definitions.h"

struct Instruction translate_multiply(char *instruction, ST_Node *node) {
       struct Instruction instruction;
       char opcode[3], rd[3], rm[3], rs[3], rn[3];
       instruction.type = MULTIPLY;
       extract_opcode(opcode, instruction);
       if (*opcode == "mla") {
	       split_4_arguments(instruction, rd, rm, rs, rn);
	       instruction.rn = search_table(node, rn);
	       instruction.accumulate = true;
       } else {
	       split_3_arguments(instruction, rd, rm, rs);
	       instruction.accumulate = false;
       }
       instruction.rd = search_table(node, rd);
       instruction.rm = search_table(node, rm);
       instruction.rs = search_table(node, rs);
       instruction.set_condition_codes = false;
       return instruction;
}

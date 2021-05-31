#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include <stdbool.h>
#include <stdint.h>
#include "definitions.h"

void data_processing(struct State *state_ptr,
		enum Opcode opcode,
		bool immediate_operand,
		bool set_condition_codes,
		uint8_t rn,
		uint8_t rd,
		uint32_t operand2);
oid multiply(struct State *state_ptr,
		struct Instruction instruction_ptr);
void single_data_transfer(struct State *state_ptr,
		bool immediate_offset,
		bool pre_post_indexing,
		bool up,
		bool load_store,
		uint8_t rn,
		uint8_t rd,
		uint32_t offset);
void branch(struct State *state_ptr, uint32_t offset);

#endif

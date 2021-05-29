#include <stdbool.h>
#include <stdint.h>
#include "definitions.h"
#include "instructions.h"

void data_processing(struct State *state_ptr,
		enum Opcode opcode,
		bool immediate_operand,
		bool set_condition_codes,
		uint8_t rn,
		uint8_t rd,
		uint32_t operand2) {
	return;
}

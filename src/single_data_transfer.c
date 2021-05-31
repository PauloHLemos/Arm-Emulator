#include <stdbool.h>
#include <stdint.h>
#include "definitions.h"
#include "instructions.h"

void single_data_transfer(struct State *state_ptr,
		bool immediate_offset,
		bool pre_post_indexing,
		bool up,
		bool load_store,
		uint8_t rn,
		uint8_t rd,
		uint32_t offset) {
	return;
}

#include <stdint.h>
#include <string.h>
#include "decode.h"
#include "definitions.h"

struct Instruction decode(uint32_t instruction_binary) {
	struct Instruction instruction;
	memset(&instruction, 0, sizeof(struct Instruction));
	instruction.cond = instruction_binary >> 28;
	
	bool bit27 = (instruction_binary & 134217728) != 0;
	bool bit26 = (instruction_binary & 67108864) != 0;
	bool bit25 = (instruction_binary & 33554432) != 0;
	bool bit7 = (instruction_binary & 128) != 0;
	bool bit4 = (instruction_binary & 16) != 0;

	if (bit27) {
		instruction.type = BRANCH;
	} else if (bit26) {
		instruction.type = SINGLE_DATA_TRANSFER;
	} else if (!bit25 && bit7 && bit4) {
		instruction.type = MULTIPLY;
	} else {
		instruction.type = DATA_PROCESSING;
	}

	if (instruction.type == DATA_PROCESSING) {
		uint32_t immediate_bitmask = 33554432;
		uint32_t opcode_bitmask = 31457280;
		uint32_t set_codes_bitmask = 1048576;
		uint32_t rn_bitmask = 983040;
		uint32_t rd_bitmask = 61440;
		uint32_t operand2_bitmask = 4095;
		instruction.immediate_operand = (instruction_binary & immediate_bitmask) != 0;
		instruction.opcode = (instruction_binary & opcode_bitmask) >> 21;
		instruction.set_condition_codes = (instruction_binary & set_codes_bitmask) != 0;
		instruction.rn = (instruction_binary & rn_bitmask) >> 16;
		instruction.rd = (instruction_binary & rd_bitmask) >> 12;
		instruction.operand2 = instruction_binary & operand2_bitmask;
	} else if (instruction.type == MULTIPLY) {
		uint32_t set_codes_bitmask = 1048576;
		uint32_t accumulate_bitmask = 2097152;
		uint32_t rd_bitmask = 983040;
		uint32_t rn_bitmask = 61440;
		uint32_t rs_bitmask = 3840;
		uint32_t rm_bitmask = 15;
		instruction.set_condition_codes = (instruction_binary & set_codes_bitmask) != 0;
		instruction.accumulate = (instruction_binary & accumulate_bitmask) != 0;
		instruction.rd = (instruction_binary & rd_bitmask) >> 16;
		instruction.rn = (instruction_binary & rn_bitmask) >> 12;
		instruction.rs = (instruction_binary & rs_bitmask) >> 8;
		instruction.rm = instruction_binary & rm_bitmask;
	} else if (instruction.type == SINGLE_DATA_TRANSFER) {
		uint32_t immediate_bitmask = 33554432;
		uint32_t indexing_bitmask = 16777216;
		uint32_t up_bitmask = 8388608;
		uint32_t load_store_bitmask = 1048576;
		uint32_t rn_bitmask = 983040;
		uint32_t rd_bitmask = 61440;
		uint32_t offset_bitmask = 4095;
		instruction.immediate_offset = (instruction_binary & immediate_bitmask) != 0;
		instruction.pre_post_indexing = (instruction_binary & indexing_bitmask) != 0;
		instruction.up = (instruction_binary & up_bitmask) != 0;
		instruction.load_store = (instruction_binary & load_store_bitmask) != 0;
		instruction.rn = (instruction_binary & rn_bitmask) >> 16;
		instruction.rd = (instruction_binary & rd_bitmask) >> 12;
		instruction.offset = instruction_binary & offset_bitmask;
	} else {
		uint32_t offset_bitmask = 16777215;
		instruction.offset = instruction_binary & offset_bitmask;
	}

	return instruction;
}




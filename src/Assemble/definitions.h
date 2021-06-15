#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdbool.h>
#include <stdint.h>

enum Instruction_Type {
	DATA_PROCESSING,
	MULTIPLY,
	SINGLE_DATA_TRANSFER,
	BRANCH
};

enum Condition {
	EQUAL, 
	NOT_EQUAL, 
	GREATER_OR_EQUAL, 
	LESS_THAN, 
	GREATER_THAN, 
	LESS_THAN_OR_EQUAL, 
	ALWAYS
};

enum Opcode {
	AND,
	EXCLUSIVE_OR,
	SUBTRACT,
	REVERSE_SUBTRACT,
	ADD,
	TEST_BITS,
	TEST_EQUALS, 
	COMPARE,     
	OR,
	MOVE
};

struct Instruction {
	enum Instruction_Type type;
	enum Condition cond;
	enum Opcode opcode;
	bool halt;
	bool immediate_operand; 
	bool immediate_offset; 
	bool set_condition_codes;
	bool accumulate;
	bool pre_post_indexing;
	bool up;
	bool load_store;
	uint8_t rd;
	uint8_t rn;
	uint8_t rm;
	uint8_t rs;
	uint32_t operand2; 
	uint32_t offset;  
};

#endif

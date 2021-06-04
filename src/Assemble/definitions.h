#ifndef DEFINITIONS_H
#define DEFINITIONS_H

enum Instruction_Type {
		DATA_PROCESSING,
		MULTIPLY,
		SINGLE_DATA_TRANSFER,
		BRANCH
};

enum Condition {
		EQUAL=0, 
		NOT_EQUAL=1, 
		GREATER_OR_EQUAL=10, 
		LESS_THAN=11, 
		GREATER_THAN=12, 
		LESS_THAN_OR_EQUAL=13, 
		ALWAYS=14
};

enum Opcode {
		AND=0,
		EXCLUSIVE_OR=1,
		SUBTRACT=2,
		REVERSE_SUBTRACT=3,
		ADD=4,
		TEST_BITS=8,
		TEST_EQUALS=9, 
		COMPARE=10,     
		OR=12,
		MOVE=13
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

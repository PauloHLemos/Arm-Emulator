#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdint.h>
#include <stdbool.h>

struct State {
	union {
		struct {
			uint32_t r0;
			uint32_t r1;
			uint32_t r2;
			uint32_t r3;
			uint32_t r4;
			uint32_t r5;
			uint32_t r6;
			uint32_t r7;
			uint32_t r8; uint32_t r9; uint32_t r10;
			uint32_t r11;
			uint32_t r12;
			uint32_t SP;
			uint32_t LR;
			uint32_t PC;
			uint32_t CPSR;
		} struct_access;
		uint32_t array_access[17];
	} registers;
	uint8_t memory[65536];
};

enum Instruction_Type {DATA_PROCESSING,
		MULTIPLY,
		SINGLE_DATA_TRANSFER,
		BRANCH};

enum Condition {EQUAL=0, 
		NOT_EQUAL=1, 
		GREATER_OR_EQUAL=10, 
		LESS_THAN=11, 
		GREATER_THAN=12, 
		LESS_THAN_OR_EQUAL=13, 
		ALWAYS=14};

enum Opcode {AND=0,
		EXCLUSIVE_OR=1,
		SUBTRACT=2,
		REVERSE_SUBTRACT=3,
		ADD=4,
		TEST_BITS=8,   //tst; test bits; and no result written
		TEST_EQUALS=9, //teq; test equals; eor no result written
		COMPARE=10,     //cmp; compare; sub no result written
		OR=12,
		MOVE=13};

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
	uint32_t operand2; // only bottom 12 bits used
	uint32_t offset;   // bottom 12 or bottom 24 bits used
};

#endif

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
			uint32_t r8;
			uint32_t r9;
			uint32_t r10;
			uint32_t r11;
			uint32_t r12;
			uint32_t SP;
			uint32_t LR;
			uint32_t PC;
			uint32_t CPSR;
		};
		uint32_t R[17];
	} registers;
	uint32_t memory[16384];
};

enum Instruction_Type {DATA_PROCESSING,
		MULTIPLY,
		SINGLE_DATA_TRANSFER,
		BRANCH};

enum Condition {EQUAL, 
		NOT_EQUAL, 
		GREATER_OR_EQUAL, 
		LESS_THAN, 
		GREATER_THAN, 
		LESS_THAN_OR_EQUAL, 
		ALWAYS};

enum Opcode {AND,
		EXCLUSIVE_OR,
		SUBTRACT,
		REVERSE_SUBTRACT,
		ADD,
		TEST_BITS,   //tst; test bits; and no result written
		TEST_EQUALS, //teq; test equals; eor no result written
		COMPARE,     //cmp; compare; sub no result written
		OR,
		MOVE};

struct Instruction {
	enum Instruction_Type type;
	enum Condition cond;
	enum Opcode opcode;
	bool halt;
	bool immediate_operand;
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

struct Pipeline {
	uint32_t (*fetch)(struct State *state_struct_ptr);
	struct Instruction (*decode)(uint32_t instruction_binary);
	bool (*execute)(struct Instruction instruction, struct State *state);
};

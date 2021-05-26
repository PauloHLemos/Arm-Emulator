#include <stdlib.h>
#include <stdint.h>

struct State {
	struct Registers {
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
	uint32_t memory[16384];
};

int main(int argc, char **argv) {
		return EXIT_SUCCESS;
}

#include "test_encode.h"
#include "encode.h"
#include "definitions.h"
#define UNUSED 0

void test_encode(void) {
	// DATA PROCESSING	       MULTIPLY			   SINGLE DATA TRANSFER	       BRANCH
	// enum Instruction_Type type; enum Instruction_Type type; enum Instruction_Type type; enum Instruction_Type type;
	// enum Condition cond;        enum Condition cond;        enum Condition cond;        enum Condition cond;
	// enum Opcode opcode;                                                                                       
	// bool immediate_operand;                                                                                     
	//                                                         bool immediate_offset;                                
	// bool set_condition_codes;   bool set_condition_codes;                                                        
	//                             bool accumulate;                                                               
	//                                                         bool pre_post_indexing;                             
	//                                                         bool up;                                  
	//                                                         bool load_store;                               
	// uint8_t rd;                 uint8_t rd;                 uint8_t rd;                              
	// uint8_t rn;                 uint8_t rn;                 uint8_t rn;                              
	//                             uint8_t rm;                                                                
	//                             uint8_t rs;                                                             
	// uint32_t operand2;                                                                                     
	//                                                         uint32_t offset;            uint32_t offset;  
	
	struct Instruction instruction;
	instruction.type = DATA_PROCESSING;
	instruction.cond = ALWAYS;
	instruction.opcode = ADD;

	uint32_t result = encode(instruction);
	printf("Test result: %d\n", result);
}

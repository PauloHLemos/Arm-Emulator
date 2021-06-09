#include "test_encode.h"
#include "encode.h"
#include "definitions.h"

void print_binary(uint32_t number) {
	char buffer[100] = "";
        for (uint32_t i = 0, mask = 1 << 31; i < 32; i++, number <<= 1) {
		if (i % 4 == 0 && i > 0) {
			strncat(buffer, " ", 1);
		}
                strncat(buffer, ((number & mask) != 0) ? "1" : "0", 1);
        }
	printf("%s\n", buffer);
}

void test_binary_equals(char *test_name, char *instruction, uint32_t expected, 
		uint32_t got, uint32_t *tests_run_ptr, uint32_t *tests_passed_ptr) {
	(*tests_run_ptr)++;	

	printf("--------------------------------------------------------------\n"
	       "Test name:\t%s\n"
	       "Instruction:\t%s\n" 
	       "Status:\t\t%s\n", 
	       test_name, instruction, (expected == got) ? "Passed" : "Failed"); 
	
	if (expected == got)  {
		(*tests_passed_ptr)++;
	} else {
		printf("\nExpected:\t");
		print_binary(expected);
		printf("Got:\t\t");	    
		print_binary(got);
	}

	printf("--------------------------------------------------------------\n");

}

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
	
	uint32_t tests_run = 0;
	uint32_t tests_passed = 0;

	struct Instruction instruction;
	instruction.type = DATA_PROCESSING;
	instruction.cond = ALWAYS;
	instruction.opcode = ADD;

	test_binary_equals("Test test", "andtests test r0", 0b00000000000000000000000000000000, 
			encode(instruction), &tests_run, &tests_passed);

	test_binary_equals("Test test 2", "thing test r0", 0b00110000010000000000000000110000, 
			encode(instruction), &tests_run, &tests_passed);

	printf("\n%d of %d tests passed correctly. \n", tests_passed, tests_run);
}

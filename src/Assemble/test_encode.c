#include <string.h>
#include "test_encode.h"
#include "encode.h"
#include "definitions.h"

void print_binary(uint32_t number) {
	char buffer[100] = "";
	char space = ' ';
        for (uint32_t i = 0, mask = 1 << 31; i < 32; i++, number <<= 1) {
		if (i % 4 == 0 && i > 0) {
			strncat(buffer, &space, 1);
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
	       "Status:\t\t%s\n", test_name, instruction, (expected == got) ? "Passed" : "Failed"); 
	
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
	instruction.type		= DATA_PROCESSING;
	instruction.cond 		= ALWAYS;
	instruction.opcode		= ADD;
	instruction.immediate_operand   = true;
	instruction.set_condition_codes = false;
	instruction.rd			= 2;
	instruction.rn 			= 1;
	instruction.operand2		= 0b000000000010;

	// DATA PROCESSING TESTS

	test_binary_equals("Test DP immediate operand", "add r2,r1,#2", 0b11100010100000010010000000000010, 
			encode(instruction), &tests_run, &tests_passed);

	instruction.opcode   = AND;
	instruction.operand2 = 0xAB;
	test_binary_equals("Test immediate hex operand", "and r2,r1,#0xAB", 0b11100010000000010010000010101011, 
			encode(instruction), &tests_run, &tests_passed);

	instruction.immediate_operand	= false;
	instruction.set_condition_codes = true;
	test_binary_equals("Test immediate hex operand, altered flags", 
			"and r2,r1,#0xAB", 0b11100000000100010010000010101011, 
			encode(instruction), &tests_run, &tests_passed);

	instruction.type = MULTIPLY;
	instruction.cond = ALWAYS;       
	instruction.set_condition_codes = false;  
	instruction.accumulate = false;           
	instruction.rd = 2;                
	// instruction.rn = 0;
	instruction.rm = 1;                
	instruction.rs = 0;                

	// MULTIPLY TESTS
	test_binary_equals("Multiply without accumulate", 
			"mul r2,r1,r0", 0b11100000000000100000000010010001, 
			encode(instruction), &tests_run, &tests_passed);
	
	instruction.rd = 3;                
	instruction.rm = 1;                
	instruction.rs = 2;                
	test_binary_equals("Multiply without accumulate 2", 
			"mul r3,r1,r2", 0b11100000000000110000001010010001, 
			encode(instruction), &tests_run, &tests_passed);

	instruction.accumulate = true;           
	instruction.rd = 3;                
	instruction.rm = 1;                
	instruction.rs = 2;                
	instruction.rn = 4;
	test_binary_equals("Multiply with accumulate", 
			"mla r3,r1,r2,r4", 0b11100000001000110100001010010001, 
			encode(instruction), &tests_run, &tests_passed);

	// SINGLE DATA TRANSFER TESTS
	instruction.type = SINGLE_DATA_TRANSFER;
	instruction.cond = ALWAYS;       
	instruction.immediate_offset = true;     
	instruction.pre_post_indexing = false;    
	instruction.up = true;                   
	instruction.load_store = true;           
	instruction.rd = 3;                
	instruction.rn = 5;                
	instruction.offset = 0b010010110100;           

	// COND -- IPU -- L Rn   Rd   Offset 
	// 0000 01 000 00 0 0000 0000 000000000000
	test_binary_equals("Single data transfer", 
			"", 0b11100110100101010011010010110100,
			encode(instruction), &tests_run, &tests_passed);
	// BRANCH TESTS
	instruction.type = BRANCH;
	instruction.cond = EQUAL;
	instruction.offset = 0b000110001001000100000001;  
	test_binary_equals("Branch", 
			"", 0b00001010000110001001000100000001,
			encode(instruction), &tests_run, &tests_passed);

	printf("\n%d of %d tests passed correctly. \n", tests_passed, tests_run);
}

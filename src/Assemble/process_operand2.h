#ifndef PROCESS_OPERAND2_H
#define PROCESS_OPERAND2_H

void process_operand2(char *operand2_string, uint32_t *operand2_ptr, bool *immediate_operand_ptr);

uint32_t process_operand2_shifted_register(char *operand2_string);

#endif

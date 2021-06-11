#ifndef SPLIT_INSTRUCTIONS_H
#define SPLIT_INSTRUCTIONS_H


void split_4_arguments_after_opcode(char *string, char *arg1, char *arg2, char *arg3, char *arg4);
void split_4_arguments(char *string, char *arg1, char *arg2, char *arg3, char *arg4);
void split_3_arguments_after_opcode(char *string, char *arg1, char *arg2, char *arg3);
void split_3_arguments(char *string, char *arg1, char *arg2, char *arg3);
void extract_opcode(char *string, char *arg1);

#endif

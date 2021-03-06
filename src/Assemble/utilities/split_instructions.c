#include <string.h>
#include "split_instructions.h"

void split_4_arguments_after_opcode(char *string, char *arg1, char *arg2, char *arg3, char *arg4) {
	*arg1 = '\0';
	*arg2 = '\0';
	*arg3 = '\0';
	*arg4 = '\0';

	// extract the opcode
	for ( ; *string != ' '; string += 1);
	for (string++; *string == ' '; string++);

	// extract 3 arguments separated by commas and optionally spaces (which will be removed)
	for ( ; *string != ','; string += 1) strncat(arg1, string, 1);
	for (string++; *string == ' '; string++);

	for ( ; *string != ','; string += 1) strncat(arg2, string, 1);
	for (string++; *string == ' '; string++);

	for ( ; *string != ','; string += 1) strncat(arg3, string, 1);
	for (string++; *string == ' '; string++);

	// extract the final argument up to the sentinel character
	for ( ; *string != '\0'; string += 1) strncat(arg4, string, 1);
}

void split_4_arguments(char *string, char *arg1, char *arg2, char *arg3, char *arg4) {
	*arg1 = '\0';
	*arg2 = '\0';
	*arg3 = '\0';
	*arg4 = '\0';

	// extract the opcode
	for ( ; *string != ' '; string += 1) strncat(arg1, string, 1);
	for (string++; *string == ' '; string++);

	// extract 2 arguments separated by commas and optionally spaces (which will be removed)
	for ( ; *string != ','; string += 1) strncat(arg2, string, 1);
	for (string++; *string == ' '; string++);

	for ( ; *string != ','; string += 1) strncat(arg3, string, 1);
	for (string++; *string == ' '; string++);

	// extract the final argument up to the sentinel character
	for ( ; *string != '\0'; string += 1) strncat(arg4, string, 1);
}

void split_3_arguments_after_opcode(char *string, char *arg1, char *arg2, char *arg3) {
	*arg1 = '\0';
	*arg2 = '\0';
	*arg3 = '\0';

	// extract the opcode
	for ( ; *string != ' '; string += 1);
	for (string++; *string == ' '; string++);

	// extract 2 arguments separated by commas and optionally spaces (which will be removed)
	for ( ; *string != ','; string += 1) strncat(arg1, string, 1);
	for (string++; *string == ' '; string++);

	for ( ; *string != ','; string += 1) strncat(arg2, string, 1);
	for (string++; *string == ' '; string++);

	// extract the final argument up to the sentinel character
	for ( ; *string != '\0'; string += 1) strncat(arg3, string, 1);
}

void split_3_arguments(char *string, char *arg1, char *arg2, char *arg3) {
	*arg1 = '\0';
	*arg2 = '\0';
	*arg3 = '\0';

	for ( ; *string != ' '; string += 1) strncat(arg1, string, 1);
	for (string++; *string == ' '; string++);

	for ( ; *string != ','; string += 1) strncat(arg2, string, 1);
	for (string++; *string == ' '; string++);

	for ( ; *string != '\0'; string += 1) strncat(arg3, string, 1);
}

void split_2_arguments_after_opcode(char *string, char *arg1, char *arg2) {
	*arg1 = '\0';
	*arg2 = '\0';

	for ( ; *string != ' '; string += 1); 
	for (string++; *string == ' '; string++);

	for ( ; *string != ','; string += 1) strncat(arg1, string, 1);
	for (string++; *string == ' '; string++);

	for ( ; *string != '\0'; string += 1) strncat(arg2, string, 1);
}

void extract_opcode(char *string, char *arg1) {
	*arg1 = '\0';
	for ( ; *string != ' '; string += 1) strncat(arg1, string, 1);
}

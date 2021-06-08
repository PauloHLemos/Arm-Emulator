CC      = gcc
#CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic
#CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -pedantic
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -pedantic

.SUFFIXES: .c .o

.PHONY: all clean

# all: assemble emulate
all: assemble
	cp ./assemble ../assemble

assemble: assemble.o
translate_data_processing: translate_data_processing.o split_instructions.o
translate_data_processing.o: test.h split_instructions.h definitions.h
split_instruction.o: split_instructions.h


clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f ../assemble
	rm -f core

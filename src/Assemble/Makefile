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
encode: encode.o test_encode.o
translate_data_processing: translate_data_processing.o split_instructions.o test.o test_translate_data_processing.o shifts.o
translate_data_processing.o: test.h split_instructions.h definitions.h test_translate_data_processing.h shifts.h
test_translate_data_processing.o: test_translate_data_processing.h definitions.h instructions.h
split_instruction.o: split_instructions.h
encode.o: encode.h definitions.h test_encode.h
test_encode.o: test_encode.h encode.h definitions.h
test.o: test.h
shifts.o: shifts.h


clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f ../assemble
	rm -f core

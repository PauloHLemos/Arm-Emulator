CC      = gcc
#CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic
#CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -pedantic
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -pedantic

.SUFFIXES: .c .o

.PHONY: all clean

# all: assemble emulate
all: emulate
	cp ./emulate ../emulate

assemble: assemble.o

emulate: emulate.o pipeline.o \
	fetch.o decode.o execute.o \
	data_processing.o multiply.o single_data_transfer.o branch.o \
	loader.o \
	process_operand2.o
emulate.o: definitions.h pipeline.h 
pipeline.o: pipeline.h definitions.h fetch.h decode.h execute.h
fetch.o: definitions.h fetch.h
decode.o: definitions.h decode.h
execute.o: execute.h instructions.h definitions.h
data_processing.o: definitions.h instructions.h process_operand2.h
multiply.o: definitions.h instructions.h
single_data_transfer.o: definitions.h instructions.h process_operand2.h
branch.o: definitions.h instructions.h
loader.o: definitions.h loader.h 
process_operand2.o: process_operand2.h definitions.h 



clean:
	rm -f $(wildcard *.o)
	rm -f emulate
	rm -f ../emulate
	rm -f core

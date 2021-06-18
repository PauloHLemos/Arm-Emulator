CC      = gcc
#CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic
#CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -pedantic
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -pedantic -Iutilities
LDLIBS  = -Lutilities -lsymbol_table -lqueue -lsplit_instructions -lshifts -lbinary_file_writer

.SUFFIXES: .c .o

.PHONY: all clean

all: libs assemble
	cp assemble ../assemble

assemble: assemble.o build_symbol_table.o convert_instructions.o encode.o translate_branch.o translate.o translate_data_processing.o translate_multiply.o translate_single_data_transfer.o process_operand2.o
libs:
	cd utilities; make; cd ..;

assemble.o: build_symbol_table.h translate.h utilities/symbol_table.h
build_symbol_table.o: build_symbol_table.h utilities/symbol_table.h
convert_instructions.o: definitions.h encode.h utilities/symbol_table.h instructions.h utilities/split_instructions.h utilities/queue.h
encode.o: encode.h definitions.h 
translate_branch.o: definitions.h utilities/symbol_table.h
translate.o: utilities/binary_file_writer.h convert_instructions.h utilities/symbol_table.h
translate_data_processing.o: definitions.h utilities/split_instructions.h utilities/shifts.h process_operand2.h instructions.h
translate_multiply.o: utilities/split_instructions.h instructions.h definitions.h
translate_single_data_transfer.o: utilities/split_instructions.h instructions.h definitions.h utilities/queue.h process_operand2.h
process_operand2.o: process_operand2.h utilities/shifts.h

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f ../assemble
	rm -f core
	cd utilities; make clean; cd ..;

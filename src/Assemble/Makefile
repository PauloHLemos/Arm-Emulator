CC      = gcc
#CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic
#CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -pedantic
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -pedantic -Ilib
LDLIBS  = -Llib -lsymbol_table -lqueue -lsplit_instructions -lshifts -lbinary_file_writer

.SUFFIXES: .c .o

.PHONY: all clean

all: libs assemble
	cp assemble ../assemble

assemble: assemble.o build_symbol_table.o convert_instructions.o encode.o translate_branch.o translate.o translate_data_processing.o translate_multiply.o translate_single_data_transfer.o 
libs:
	cd lib; make; cd ..;

assemble.o: build_symbol_table.h translate.h lib/symbol_table.h
build_symbol_table.o: build_symbol_table.h lib/symbol_table.h
convert_instructions.o: definitions.h encode.h lib/symbol_table.h instructions.h lib/split_instructions.h lib/queue.h
encode.o: encode.h definitions.h 
translate_branch.o: definitions.h lib/symbol_table.h
translate.o: lib/binary_file_writer.h convert_instructions.h lib/symbol_table.h
translate_data_processing.o: definitions.h lib/split_instructions.h lib/shifts.h process_operand2.h instructions.h
translate_multiply.o: lib/split_instructions.h instructions.h definitions.h
translate_single_data_transfer.o: lib/split_instructions.h instructions.h definitions.h lib/queue.h process_operand2.h

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f ../assemble
	rm -f core
	cd lib; make clean; cd ..;

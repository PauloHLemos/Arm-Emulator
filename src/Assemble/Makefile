CC      = gcc
#CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic
#CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -pedantic
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -pedantic -Isymbol_table
LDLIBS  = -Lsymbol_table -lsymbol_table

.SUFFIXES: .c .o

.PHONY: all clean

all: libs assemble
	cp assemble ../assemble

assemble: assemble.o build_symbol_table.o convert_instructions.o encode.o queue.o shifts.o split_instructions.o translate_branch.o translate.o translate_data_processing.o translate_multiply.o translate_single_data_transfer.o binary_file_writer.o
libs:
	cd symbol_table; make; cd ..;

assemble.o: build_symbol_table.h translate.h symbol_table/symbol_table.h
build_symbol_table.o: build_symbol_table.h symbol_table/symbol_table.h
convert_instructions.o: definitions.h encode.h symbol_table/symbol_table.h instructions.h split_instructions.h queue.h
encode.o: encode.h definitions.h 
queue.o: queue.h
shifts.o: shifts.h definitions.h
split_instructions.o: split_instructions.h
translate_branch.o: definitions.h symbol_table/symbol_table.h
translate.o: binary_file_writer.h convert_instructions.h symbol_table/symbol_table.h
translate_data_processing.o: definitions.h split_instructions.h shifts.h process_operand2.h instructions.h
translate_multiply.o: split_instructions.h instructions.h definitions.h
translate_single_data_transfer.o: split_instructions.h instructions.h definitions.h queue.h process_operand2.h
binary_file_writer.o: binary_file_writer.h

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f ../assemble
	rm -f core
	cd symbol_table; make clean; cd ..;

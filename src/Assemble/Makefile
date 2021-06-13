CC      = gcc
#CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic
#CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -pedantic
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -pedantic -Isymbol_table
LDLIBS  = -Lsymbol_table -lsymbol_table

.SUFFIXES: .c .o

.PHONY: all clean

all: libs assemble
	cp assemble ../assemble

assemble: assemble.o build_symbol_table.o convert_instructions.o encode.o queue.o shifts.o split_instruction.o translate_branch.o translate.o translate_data_processing.o translate_multiply.o translate_single_data_transfer.o
libs:
	cd symbol_table; make; cd ..;



assemble.o: build_symbol_table.h translate.h symbol_table/symbol_table.h
build_symbol_table.o: build_symbol_table.h symbol_table/symbol_table.h
convert_instructions.o: definitions.h encode.h symbol_table/symbol_table.h instructions.h split_instructions.h queue.h
encode.o: encode.h definitions.h 
queue.o: queue.h
shifts.o: shifts.h definitions.h
split_instruction.o: split_instruction.h
translate_branch.o: definitions.h symbol_table/symbol_table.h
translate.o: binary_file_writer.h convert_instructions.h symbol_table/symbol_table.h
translate_data_processing.o: definitions.h split_instruction.h shifts.h
translate_multiply.o: split_instructions.h instructions.h definitions.h
translate_single_data_transfer.o: split_instructions.h instructions.h definitions.h queue.h


build_symbol_table: build_symbol_table.o 
translate_data_processing: translate_data_processing.o split_instructions.o test.o test_translate_data_processing.o shifts.o
test: translate_multiply.o translate_data_processing.o translate_branch.o translate_single_data_transfer.o encode.o convert_instructions.o shifts.o split_instructions.o
encode: encode.o test_encode.o
test_translate_data_processing.o: test_translate_data_processing.h definitions.h instructions.h
test_encode.o: test_encode.h encode.h definitions.h
test.o: test.h



#build_symbol_table.o: symbol_table.h

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f ../assemble
	rm -f core
	cd symbol_table; make clean; cd ..;

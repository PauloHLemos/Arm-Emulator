CC      = gcc
#CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic
#CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -pedantic
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -pedantic -Ilib
LDLIBS  = -Llib -lsymbol_table

.SUFFIXES: .c .o

.PHONY: all clean

# all: assemble emulate
all: libs build_symbol_table assemble
	cp assemble ../assemble

assemble: assemble.o build_symbol_table.o translate.o
encode: encode.o test_encode.o
assemble.o: build_symbol_table.h translate.h symbol_table.h
translate_data_processing: translate_data_processing.o split_instructions.o test.o test_translate_data_processing.o shifts.o
translate_data_processing.o: test.h split_instructions.h definitions.h test_translate_data_processing.h shifts.h
test_translate_data_processing.o: test_translate_data_processing.h definitions.h instructions.h
split_instruction.o: split_instructions.h
encode.o: encode.h definitions.h test_encode.h
test_encode.o: test_encode.h encode.h definitions.h
test.o: test.h
shifts.o: shifts.h
translate.o: translate.h symbol_table.h
build_symbol_table.o: build_symbol_table.h symbol_table.h

build_symbol_table: build_symbol_table.o symbol_table.o

libs:
	cd lib; make; cd ..;

#build_symbol_table.o: symbol_table.h

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f ../assemble
	rm -f core
	cd lib; make clean; cd ..;

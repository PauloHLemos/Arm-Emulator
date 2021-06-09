CC      = gcc
#CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic
#CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -pedantic
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -pedantic -Isymbol_table
LDLIBS  = -Lsymbol_table -lsymbol_table

.SUFFIXES: .c .o

.PHONY: all clean

# all: assemble emulate
all: assemble
	cp assemble ../assemble

assemble: assemble.o

build_symbol_table: libs build_symbol_table.o #symbol_table.o

libs:
	cd symbol_table; make

#build_symbol_table.o: symbol_table.h

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f ../assemble
	rm -f core
	cd symbol_table; make clean

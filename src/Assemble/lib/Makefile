CC	=	gcc
CFLAGS	=	-g -Wall
BUILD   = 	libsymbol_table.a libqueue.a libshifts.a libsplit_instructions.a

all: $(BUILD)

clean:
	/bin/rm -f $(BUILD) *.o core

libsymbol_table.a: symbol_table.o
	ar rcs libsymbol_table.a symbol_table.o
libqueue.a: queue.o
	ar rcs libqueue.a queue.o
libshifts.a: shifts.o
	ar rcs libshifts.a shifts.o
libsplit_instructions.a: split_instructions.o
	ar rcs libsplit_instructions.a split_instructions.o

symbol_table.o:	symbol_table.h
queue.o: queue.h
shifts.o: shifts.h
split_instructions.o: split_instructions.h

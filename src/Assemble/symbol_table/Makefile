CC	=	gcc
CFLAGS	=	-Wall
LIB	=	libsymbol_table.a
LIBOBJS =	symbol_table.o
BUILD   = 	$(LIB)

all: $(BUILD)

clean:
	/bin/rm -f $(BUILD) *.o core

$(LIB):		$(LIBOBJS)
	ar rcs $(LIB) $(LIBOBJS)

symbol_table.o:	symbol_table.h

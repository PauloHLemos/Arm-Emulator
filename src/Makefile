CC      = gcc
#CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic
#CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -pedantic
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -pedantic

.SUFFIXES: .c .o

.PHONY: all clean

all: assemble emulate

assemble: assemble.o

emulate: emulate.o pipeline.o fetch.o decode.o execute.o
emulate.o: definitions.h pipeline.h 
pipeline.o: pipeline.h definitions.h fetch.h decode.h execute.h
fetch.o: fetch.h
decode.o: decode.h
execute.o: execute.h



clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate
	rm -f core

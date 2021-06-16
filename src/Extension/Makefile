CC      = gcc
#CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic
#CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -pedantic
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -pedantic -lm
LDLIBS  = -lm

.SUFFIXES: .c .o

.PHONY: all clean

all: main

test: test.o image_loader.o image_storer.o utils.o
test.o: image_loader.h image_storer.h utils.h

image_loader.o: image_loader.h stb/stb_image.h 
image_storer.o: image_storer.h stb/stb_image.h stb/stb_image_write.h 
utils.o: utils.h definitions.h
main.o: main.c

clean:
	rm -f $(wildcard *.o)
	rm -f core

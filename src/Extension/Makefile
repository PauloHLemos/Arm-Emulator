CC      = gcc
#CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic
#CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -pedantic
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -pedantic

.SUFFIXES: .c .o

.PHONY: all clean

# all: emulate
# 	cp ./emulate ../emulate


clean:
	rm -f $(wildcard *.o)
#	rm -f emulate
#	rm -f ../emulate
	rm -f core

CC      = gcc
#CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic
#CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -pedantic
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -pedantic -lm
LDLIBS  = -lm

.SUFFIXES: .c .o

.PHONY: all clean

all: main

main: main.o image_loader.o image_storer.o utils.o image_manipulation.o generate_kernel.o video_processor.o 
test: test.o image_loader.o image_storer.o utils.o image_manipulation.o 
test.o: image_loader.h image_storer.h utils.h

image_loader.o: image_loader.h stb/stb_image.h 
image_storer.o: image_storer.h stb/stb_image.h stb/stb_image_write.h 
utils.o: utils.h definitions.h
main.o: utils.h image_storer.h image_loader.h image_manipulation.h generate_kernel.h definitions.h
image_manipulation.o: image_manipulation.h definitions.h
generate_kernel.o: generate_kernel.h 
video_processor.o: video_processor.h definitions.h

clean:
	rm -f $(wildcard *.o)
	rm -f core

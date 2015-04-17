CC=gcc
FUSE_CFLAGS=$(shell pkg-config fuse --cflags --libs)
CFLAGS=-g $(FUSE_CFLAGS) -D_FILE_OFFSET_BITS=64 -lm
CFLAGS_O=-g -c $(FUSE_CFLAGS) 
O_FILES=$(patsubst %.c,%.o,$(wildcard *.c))

all: build
 
build: $(O_FILES)
	$(CC) $(CFLAGS) $(O_FILES) -o mathfs
    
clean:
	rm -rf *.o mathfs

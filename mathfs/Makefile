CC=gcc
FUSE_CFLAGS=$(shell pkg-config fuse --cflags --libs)
CFLAGS=-g $(FUSE_CFLAGS) -D_FILE_OFFSET_BITS=64 -lm
CFLAGS_O=-g -c $(FUSE_CFLAGS) 
O_FILES=$(patsubst %.c,%.o,$(wildcard *.c))

all: build
 
build: $(O_FILES)
	$(CC) $(O_FILES) $(CFLAGS) -o mathfs-run
clean:
	rm -rf *.o mathfs

/*
  FUSE: Filesystem in Userspace
  Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>
  This program can be distributed under the terms of the GNU GPL.
  See the file COPYING.
  gcc -Wall hello.c `pkg-config fuse --cflags --libs` -o hello
*/

#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#define TABLE_SIZE 9
static const char *paths[TABLE_SIZE];
static const char *strings[TABLE_SIZE];

int compareFile(const char *path, const char *paths[]);
const char *returnMatch(const char *path, const char *paths[], const char *strings[]);


// Returns 1 if we find a match. Returns 0 otherwise
int compareFile(const char *path, const char *paths[]) {
	int i;
	for(i = 0; i < TABLE_SIZE; i++) {
		if(strcmp(path,paths[i]) == 0)
			return 1;
	}
	
	return 0;

}

const char *returnMatch(const char *path, const char *paths[], const char *strings[]) {
	int i;
	for(i = 0; i < TABLE_SIZE; i++) {
		if(strcmp(path,paths[i]) == 0)
			return strings[i];	
	}

	const char *null;
	null = NULL;
	return null;

}

void initializeFS(const char *paths[], const char *strings[]) {


	paths[0] = "/factor";
        paths[1] = "/fib";
        paths[2] = "/add";
        paths[3] = "/sub";
        paths[4] = "/mul";
        paths[5] = "/div";
        paths[6] = "/exp";
        paths[7] = "/hello";
        paths[8] = "/sup";

        strings[0] = "Factor\n";
        strings[1] = "Fib\n";
        strings[2] = "Add\n";
        strings[3] = "Sub\n";
        strings[4] = "Mul\n";
        strings[5] = "Div\n";
        strings[6] = "Exp\n";
        strings[7] = "Hello World!\n";
        strings[8] = "Hi There!\n";
}

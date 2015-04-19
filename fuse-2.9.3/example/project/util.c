
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

#define TABLE_SIZE 7
static const char *dirPaths[TABLE_SIZE];
static const char *strings[TABLE_SIZE];

// Returns 1 if we find a match. Returns 0 otherwise
int compareDirs(const char *path, const char *dirPaths[]) {
	int i;
	for(i = 0; i < TABLE_SIZE; i++) {
		if(strcmp(path,dirPaths[i]) == 0)
			return 1;
	}
	
	return 0;

}

const char *returnMatch(const char *path, const char *dirPaths[], const char *strings[]) {
	int i;
	for(i = 0; i < TABLE_SIZE; i++) {
		if(strcmp(path,dirPaths[i]) == 0)
			return strings[i];	
	}

	const char *null;
	null = NULL;
	return null;

}

void initializeFS(const char *dirPaths[], const char *strings[]) {


	dirPaths[0] = "/factor";
        dirPaths[1] = "/fib";
        dirPaths[2] = "/add";
        dirPaths[3] = "/sub";
        dirPaths[4] = "/mul";
        dirPaths[5] = "/div";
        dirPaths[6] = "/exp";

        strings[0] = "Factor\n";
        strings[1] = "Fib\n";
        strings[2] = "Add\n";
        strings[3] = "Sub\n";
        strings[4] = "Mul\n";
        strings[5] = "Div\n";
        strings[6] = "Exp\n";
}

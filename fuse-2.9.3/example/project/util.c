
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

// Returns 1 if we find a match. Returns 0 otherwise
int compareDirs(const char *path, const char *dirPaths[]) {
	int i;
	for(i = 0; i < TABLE_SIZE; i++) {
		if(strcmp(path,dirPaths[i]) == 0)
			return 1;
	}
	
	return 0;

}

int compareDocs(const char *path, const char *docPaths[]) {
	int i;
	for(i = 0; i < TABLE_SIZE; i++) {
		if(strcmp(path,docPaths[i]) == 0)
			return 1;
	}
	
	return 0;

}

const char *returnDoc(const char *path, const char *docPaths[], const char *docs[]) {
	int i;
	for(i = 0; i < TABLE_SIZE; i++) {
		if(strcmp(path,docPaths[i]) == 0)
			return docs[i];	
	}

	const char *null;
	null = NULL;
	return null;

}


const char *returnMatch(const char *path, const char *dirPaths[], const char *docs[]) {
	int i;
	for(i = 0; i < TABLE_SIZE; i++) {
		if(strcmp(path,dirPaths[i]) == 0)
			return dirPaths[i];	
	}

	const char *null;
	null = NULL;
	return null;

}

void initializeFS(const char *dirPaths[], const char *docPaths[], const char *docs[]) {

	printf("\t\t\tCall to initialize\n");

	dirPaths[0] = "/factor";
        dirPaths[1] = "/fib";
        dirPaths[2] = "/add";
        dirPaths[3] = "/sub";
        dirPaths[4] = "/mul";
        dirPaths[5] = "/div";
        dirPaths[6] = "/exp";

	docPaths[0] = "/factor/doc";
        docPaths[1] = "/fib/doc";
        docPaths[2] = "/add/doc";
        docPaths[3] = "/sub/doc";
        docPaths[4] = "/mul/doc";
        docPaths[5] = "/div/doc";
        docPaths[6] = "/exp/doc";

        docs[0] = "Show the prime factors of a number.\nThe file factor/n contains the prime factors of n.\n";
        docs[1] = "The file fib/n contains the first n fibonacci numbers.\n";
        docs[2] = "Add two numbers.\nThe file add/a/b contains the sum a+b\n";
        docs[3] = "Subtract two numbers.\nThe file sub/a/b contains the difference a-b.\n";
        docs[4] = "Multiply two numbers.\nThe file mul/a/b contains the product a*b.\n";
        docs[5] = "Divide two numbers.\nThe file div/a/b contains the quotient of a/b.\n";
        docs[6] = "Raise a number to an exponent.\nThe file exp/a/b contains a raised to the power of b.\n";
}

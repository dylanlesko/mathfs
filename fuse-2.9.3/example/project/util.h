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


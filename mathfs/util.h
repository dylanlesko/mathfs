#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>

void initializeFS(const char *dirPaths[], const char *docPaths[], const char *docs[]);
int compareFile(const char *path, const char *dirPaths[]);
int compareDoc(const char *path, const char *docPaths[]);
int is_dir( const char *path, const char *dirPaths[]);
int is_path( const char *path, const char *dirPaths[]);
int is_doc(const char *path, const char *docPaths[]);
const char *returnMatch(const char *path, const char *dirPaths[], const char *strings[]);
const char *returnDoc(const char *path, const char *docPaths[], const char *docs[]);



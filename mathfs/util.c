#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <fuse/fuse.h>
#include <ctype.h>

#define TABLE_SIZE 7
void initializeFS(const char *dirPaths[], const char *docPaths[], const char *docs[]) {
        printf("Call to initialize\n");

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

        docs[0]  = "Show the prime factors of a number.\nThe file factor/n contains the prime factors of n.\n";
        docs[1]  = "The file fib/n contains the first n fibonacci numbers.\n";
        docs[2]  = "Add two numbers.\nThe file add/a/b contains the sum a+b\n";
        docs[3]  = "Subtract two numbers.\nThe file sub/a/b contains the difference a-b.\n";
        docs[4]  = "Multiply two numbers.\nThe file mul/a/b contains the product a*b.\n";
        docs[5]  = "Divide two numbers.\nThe file fiv/a/b contains the quotient of a/b.\n";
        docs[6]  = "Raise a number to an exponent.\nThe file exp/a/b contains a raised to the power of b.\n";

}

// Returns 1 if we find a match. Returns 0 otherwise
int compareFile(const char *path, const char *dirPaths[]) {
        int i;
        for(i = 0; i < TABLE_SIZE; i++) {
                if(strncmp(path,dirPaths[i], strlen(dirPaths[i])) == 0)
                //if(strcmp(path,paths[i]) == 0)
                        return 1;
        }

        return 0;
}

// Returns 1 if we find a match. Returns 0 otherwise
int compareDoc(const char *path, const char *docPaths[]) {
        int i;
        for(i = 0; i < TABLE_SIZE; i++) {
                if(strncmp(path,docPaths[i], strlen(docPaths[i])) == 0)
                //if(strcmp(path,paths[i]) == 0)
                        return 1;
        }

        return 0;
}


int is_dir( const char *path, const char *dirPaths[] )
{
        printf("\t\tInside is_dir\n");
        int i;
        for(i = 0; i < TABLE_SIZE; i++) {
                if(strcmp(path,dirPaths[i]) == 0)
                        return 1;
        }
        return 0;
}

int is_path( const char *path, const char *dirPaths[] )
{
        printf("\t\tInside is_path\n");

        int i;
        for(i = 0; i < TABLE_SIZE; i++) {
                if(strncmp(path,dirPaths[i], strlen(dirPaths[i])) == 0)
                        return 1;
        }
        return 0;
}

int is_doc(const char *path, const char *docPaths[]) {

        printf("\t\tInside is_doc\n");
        int i;
        for(i = 0; i < TABLE_SIZE; i++) {
                if(strcmp(path,docPaths[i]) == 0)
                        return 1;
        }
        return 0;
}

const char *returnMatch(const char *path, const char *dirPaths[], const char *docs[]) {
        int i;
        for(i = 0; i < TABLE_SIZE; i++) {
                //if(strncmp(path,dirPaths[i], strlen(dirPaths[i])) == 0)
                if(strcmp(path,dirPaths[i]) == 0)
                        return docs[i];
        }

        const char *null;
        null = NULL;
        return null;

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


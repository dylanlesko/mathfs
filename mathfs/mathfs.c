#define FUSE_USE_VERSION 26

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <fuse/fuse.h>
#include <ctype.h>
#include "defs.h"

static const char *paths[TABLE_SIZE];
static const char *docs[TABLE_SIZE];

const char *pathfs[TABLE_SIZE] = { "add", "sub", "mul", "div", "exp", "factor", "fib" };


int get_index( const char *path )
{
	int i;
	for(i = 0; i < TABLE_SIZE; i++) {
		if(strcmp(path,pathfs[i]) == 0)
			return i;
	}
	return -1;	
}

int is_dir( const char *path, const char *paths[] )
{
	int i;
	for(i = 0; i < TABLE_SIZE; i++) {
		if(strcmp(path,paths[i]) == 0)
			return 1;
	}
	return 0;
}

int is_path( const char *path, const char *paths[] )
{	
	int i;
	for(i = 0; i < TABLE_SIZE; i++) {
		if(strncmp(path,paths[i], strlen(paths[i])) == 0)
			return 1;
	}
	return 0;
}

const char *returnMatch(const char *path, const char *paths[], const char *strings[]) {
	int i;
	for(i = 0; i < TABLE_SIZE; i++) {
		//if(strncmp(path,paths[i], strlen(paths[i])) == 0)
		if(strcmp(path,paths[i]) == 0)
			return docs[i];	
	}

	const char *null;
	null = NULL;
	return null;

}

// FUSE function implementations.
static int mathfs_getattr(const char *path, struct stat *stbuf)
{
	int res; 
	res = 0;
	
	printf(MAKE_RED"\t\tgetattr with path (\"%s\")"RESET_FORMAT,path);
	printf("\n");
	int argCount = 0;

	memset(stbuf, 0, sizeof(struct stat));

	if (strcmp(path, "/") == 0) {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
	}
	else if(is_dir(path,paths)) 
	{
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
		stbuf->st_size = strlen(path);

	} 
	else if( is_path( path, paths) )
	{
		char *tempToken = malloc(strlen(path) + 1);
		strcpy(tempToken, path);
		tempToken[strlen(path) + 1] = '\0';
		tempToken = strtok(tempToken, "/");
		char *hold;
		char returnValue[2048];

		char *operation;
		char *arg1;
		char *arg2;

		operation = malloc(strlen(tempToken) + 1);
		strcpy(operation, tempToken);

		arg1 = malloc(strlen(path) + 1 );
		arg2 = malloc(strlen(path) + 1 );

		while( tempToken != NULL )
		{
			printf(MAKE_YELLOW"\t\ttoken: (\"%s\")"RESET_FORMAT, tempToken);
			printf("\n");
			strcpy(hold, tempToken);

			if(argCount == 1)
			{
				strcpy(arg1, tempToken);
			}
			else if(argCount == 2)
			{
				strcpy(arg2, tempToken);
			}
			argCount++;

			tempToken = strtok(NULL, "/");
		}

		/*
		*	count = 1 		math/add
		*	count = 2 		math/add/1
		*	count = 3 		math/add/1/2
		*/
		if( argCount == 2 )
		{
			if(strcmp(hold, "doc") == 0 )
			{
				stbuf->st_mode = S_IFREG | 0444;
				stbuf->st_nlink = 1;
				stbuf->st_size = strlen(path);
			}	
			else if( (strcmp(operation, "fib") == 0) || (strcmp(operation, "factor") == 0) )
			{
				printf(MAKE_BLUE"These should have one arg.."RESET_FORMAT);
				stbuf->st_mode = S_IFREG | 0444;
				stbuf->st_nlink = 1;
				//stbuf->st_size = strlen(path);
				strcpy( returnValue, mathOperation( operation, arg1, arg2 ) );
				stbuf->st_size = strlen(returnValue);
				printf("\n\tmath returns: %s\n", returnValue);	
			}
			else
			{
				stbuf->st_mode = S_IFDIR | 0444;
				stbuf->st_nlink = 1;
				//stbuf->st_size = strlen(path);
				strcpy( returnValue, mathOperation( operation, arg1, arg2 ) );
				stbuf->st_size = strlen(returnValue);	
				printf("\n\tmath returns: %s\n", returnValue);	
			}	
		}
		else if( argCount == 3)
		{
			if( (strcmp(operation, "fib") != 0) && (strcmp(operation, "factor") != 0) )
			{
				stbuf->st_mode = S_IFDIR | 0444;
				stbuf->st_nlink = 1;
				strcpy( returnValue, mathOperation( operation, arg1, arg2 ) );
				stbuf->st_size = strlen(returnValue);
				printf("\n\tmath returns: %s\n", returnValue);	
			}
			else
			{
				res = -ENOENT;
			}
		}
		else
		{
			res = -ENOENT;
		}

		FREE(tempToken);
		FREE(arg1);
		FREE(arg2);
		FREE(operation);
	}

	else
	{
		res = -ENOENT;
	}
	return res;
}

static int mathfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset,
			struct fuse_file_info *fi)
{
	printf(MAKE_BLUE"\t\treaddir with path (\"%s\")"RESET_FORMAT,path);
	printf("\n");
	
	(void) offset;
	(void) fi;

	filler(buf, ".", NULL, 0);
	filler(buf, "..", NULL, 0);

	if (strcmp(path, "/") == 0 )
	{
		int i;
		for(i = 0; i < TABLE_SIZE; i++) 
			filler(buf, paths[i] + 1, NULL, 0);
	}
	else if(is_dir(path,paths))
	{
		const char *newString = "/doc";		
		filler(buf, newString + 1, NULL, 0);
	}
	else
		return -ENOENT;

	


	

	return 0;
}		

static int mathfs_open(const char *path, struct fuse_file_info *fi)
{	
	printf(MAKE_GREEN"\t\topen with path (\"%s\")"RESET_FORMAT,path);
	printf("\n");
	fi = fi;

	// No match	
	if (is_dir(path,paths) == 0)
		return -ENOENT;

	if ((fi->flags & 3) != O_RDONLY)
		return -EACCES;
	

	return 0;
}

static int mathfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
	printf(MAKE_PURPLE"\t\tread with path (\"%s\")"RESET_FORMAT,path);
	printf("\n");

	size_t len;
	(void) fi;
	if(is_dir(path,paths) == 0)
		return -ENOENT;

	const char *path_str;
	path_str = returnMatch(path,paths,docs);

	len = strlen(path_str);
	if (offset < len) {
		if (offset + size > len)
			size = len - offset;
		memcpy(buf, path_str + offset, size);
		
	} else
		size = 0;

	return size;
}

static struct fuse_operations mathfs_oper = {
    .getattr = mathfs_getattr,
    .readdir = mathfs_readdir,
    .open = mathfs_open,
    .read = mathfs_read,
};

int main(int argc, char **argv)
{
	paths[0] = "/add";
	paths[1] = "/sub";
	paths[2] = "/mul";
	paths[3] = "/div";
	paths[4] = "/exp";
	paths[5] = "/factor";
	paths[6] = "/fib";

	docs[0] = "Add\n";
	docs[1] = "Sub\n";
	docs[2] = "Mul\n";
	docs[3] = "Div\n";
	docs[4] = "Exp\n";
	docs[5] = "Factor\n";
	docs[6] = "Fib\n";

    return fuse_main(argc, argv, &mathfs_oper, NULL);
}


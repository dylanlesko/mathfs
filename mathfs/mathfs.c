#define FUSE_USE_VERSION 26

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <fuse/fuse.h>
#include <ctype.h>
 
#define RESET_FORMAT "\e[m"
#define MAKE_GREEN "\e[32m"
#define MAKE_RED "\e[31m"
#define MAKE_BLACK "\e[30m"
#define MAKE_YELLOW "\e[33m"
#define MAKE_BLUE "\e[34m"
#define MAKE_PURPLE "\e[35m"
#define MAKE_CYAN "\e[36m"
#define MAKE_WHITE "\e[37m"
#define MAKE_UNDERLINE "\e[4m"


#define TABLE_SIZE 10
static const char *paths[TABLE_SIZE];
static const char *docs[TABLE_SIZE];

int compareFile(const char *path, const char *paths[]);
const char *returnMatch(const char *path, const char *paths[], const char *strings[]);


// Returns 1 if we find a match. Returns 0 otherwise
int compareFile(const char *path, const char *paths[]) {
	int i;
	for(i = 0; i < TABLE_SIZE; i++) {
		if(strncmp(path,paths[i], strlen(paths[i])) == 0)
		//if(strcmp(path,paths[i]) == 0)
			return 1;
	}
	
	return 0;
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


		char *operation;
		char *arg1;
		char *arg2;

		operation = malloc(strlen(tempToken) + 1);
		strcpy(operation, tempToken);
	

		while( tempToken != NULL )
		{
			printf(MAKE_YELLOW"\t\ttoken: (\"%s\")"RESET_FORMAT, tempToken);
			printf("\n");
			strcpy(hold, tempToken);
			tempToken = strtok(NULL, "/");
			argCount++;
			if(argCount < 3)
			{
				//strcpy(pathArray[argCount], tempToken);
			}
		}

	//	printf("first: %s", pathArray[0]);

		printf("count: %d\n", argCount);
		/*
		*	count = 1 		math/add
		*	count = 2 		math/add/1
		*	count = 3 		math/add/1/2
		*/
		if( argCount == 1 )
		{
			printf("operation dir\n");
		}
		else if( argCount == 2 )
		{
			if(strcmp(hold, "doc") == 0 )
			{
				stbuf->st_mode = S_IFREG | 0444;
				stbuf->st_nlink = 1;
				stbuf->st_size = strlen(path);
			}	
			else
			{
				stbuf->st_mode = S_IFDIR | 0444;
				stbuf->st_nlink = 1;
				stbuf->st_size = strlen(path);		
			}	
		}
		else if( argCount == 3)
		{
			stbuf->st_mode = S_IFREG | 0444;
			stbuf->st_nlink = 1;
			stbuf->st_size = strlen(path);
		}

		free(tempToken);
		free(operation);
	}

	else
		res = -ENOENT;
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
	else if(compareFile(path,paths))
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
	if (compareFile(path,paths) == 0)
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
	if(compareFile(path,paths) == 0)
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
	paths[0] = "/factor";
	paths[1] = "/fib";
	paths[2] = "/add";
	paths[3] = "/sub";
	paths[4] = "/mul";
	paths[5] = "/div";
	paths[6] = "/exp";
	paths[7] = "/hello";
	paths[8] = "/sup";
	paths[9] = "/add/f";

	docs[0] = "Factor\n";
	docs[1] = "Fib\n";
	docs[2] = "Add\n";
	docs[3] = "Sub\n";
	docs[4] = "Mul\n";
	docs[5] = "Div\n";
	docs[6] = "Exp\n";
	docs[7] = "Hello World!\n";
	docs[8] = "Hi There!\n";

    return fuse_main(argc, argv, &mathfs_oper, NULL);
}


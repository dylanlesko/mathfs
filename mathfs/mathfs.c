#define FUSE_USE_VERSION 26

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <fuse/fuse.h>
 

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

// FUSE function implementations.
static int mathfs_getattr(const char *path, struct stat *stbuf)
{
	int res; 
	res = 0;
	
	printf("\t\t\tgetattr with path %s\n",path);
	
	memset(stbuf, 0, sizeof(struct stat));
	
	if (strcmp(path, "/") == 0) {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
	} 

	memset(stbuf, 0, sizeof(struct stat));

	if (strcmp(path, "/") == 0) {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;

	}
	 else if(compareFile(path,paths)) {

		// Find the corresponding string to get the size
		const char *path_string;
		path_string = returnMatch(path,paths,strings);
		
		stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		stbuf->st_size = strlen(path_string);
	} else
		res = -ENOENT;
	return res;
}

static int mathfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset,
			struct fuse_file_info *fi)
{
	printf("\t\t\treaddir with path %s\n",path);
	
	return 0;
}		

static int mathfs_open(const char *path, struct fuse_file_info *fi)
{	
	printf("\t\t\topen with path %s\n",path);
		
	return 0;
}

static int mathfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
	printf("\t\t\tread with path %s\n",path);
	
	return 0;
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

	strings[0] = "Factor\n";
	strings[1] = "Fib\n";
	strings[2] = "Add\n";
	strings[3] = "Sub\n";
	strings[4] = "Mul\n";
	strings[5] = "Div\n";
	strings[6] = "Exp\n";
	strings[7] = "Hello World!\n";
	strings[8] = "Hi There!\n";

    return fuse_main(argc, argv, &mathfs_oper, NULL);
}


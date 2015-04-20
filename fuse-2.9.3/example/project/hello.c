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
static const char *docPaths[TABLE_SIZE];
static const char *docs[TABLE_SIZE];


static const char *hello_str = "Hello World!\n";
static const char *hello_path = "/add/hello";



// This function determines whether the path is a file or a directory
static int hello_getattr(const char *path, struct stat *stbuf)
{
	int res; res = 0;

	printf("\t\t\tgetattr with path %s\n",path);


	memset(stbuf, 0, sizeof(struct stat));

	if (strcmp(path, "/") == 0) {
		printf("\t\t\tRoot of getattr\n");
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
	} else if(strcmp(path,hello_path) == 0) {
		stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		stbuf->st_size = strlen(hello_str);
	} else if(compareDirs(path,dirPaths)) {
		printf("\t\t\tDirectory of getattr\n");
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
	} else {
		printf("\t\t\treached error with path %s\n",path);
		res = -ENOENT;
	}


	return res;
}

static int hello_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
			 off_t offset, struct fuse_file_info *fi)
{

	printf("\t\t\treaddir with path %s\n",path);
	
	(void) offset;
	(void) fi;

/*
	1) If the path equals any of the directory paths, return the directory path
		else, return -ENOENT
	2) For all entries in the directory, put each entry into the buffer.	

*/



	if(strcmp(path, "/") == 0) {
		printf("\t\t\tInside the root filler\n\n");
		filler(buf, ".", NULL, 0);
		filler(buf, "..", NULL, 0);

		int i, res;
		for(i = 0; i < TABLE_SIZE; i++)  {
			res = filler(buf, dirPaths[i] + 1, NULL, 0);
			printf("\t\t\tFiller result is: %u\n",res);		

		}
	} else if(strcmp(path,"/add") == 0) {
		printf("\t\t\tEntered the /add section of readdir\n");
		filler(buf,".",NULL,0);
		filler(buf,"..",NULL,0);
		filler(buf,hello_path,NULL,0);
	} else {
		printf("\t\t\tReached error with readdir and path %s\n",path);
		return -ENOENT;
	}

	return 0;
}

static int hello_open(const char *path, struct fuse_file_info *fi)
{

	 printf("\t\t\topen with path %s\n",path);

	// No match	
	if (strcmp(path, hello_path) != 0)
		return -ENOENT;

	if ((fi->flags & 3) != O_RDONLY)
		return -EACCES;
	

	return 0;
}

static int hello_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{

	printf("\t\t\tread with path %s\n",path);

	size_t len;
	(void) fi;
	if(strcmp(path, hello_path) != 0)
		return -ENOENT;


	len = strlen(hello_str);
	if (offset < len) {
		if (offset + size > len)
			size = len - offset;
		memcpy(buf, hello_str + offset, size);
		
	} else
		size = 0;

	return size;
}


static struct fuse_operations hello_oper = {
	.getattr	= hello_getattr,
	.readdir	= hello_readdir,
	.open		= hello_open,
	.read		= hello_read,
};

int main(int argc, char *argv[])
{
	initializeFS(dirPaths,docPaths,docs);
	return fuse_main(argc, argv, &hello_oper, NULL);
}


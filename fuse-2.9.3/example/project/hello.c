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

// This function determines whether the path is a file or a directory
static int hello_getattr(const char *path, struct stat *stbuf)
{
	int res; res = 0;

	printf("\t\t\tgetattr with path %s\n",path);


	memset(stbuf, 0, sizeof(struct stat));

	if (strcmp(path, "/") == 0) {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
	} else if(compareFile(path,paths)) {

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

static int hello_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
			 off_t offset, struct fuse_file_info *fi)
{

	printf("\t\t\treaddir with path %s\n",path);
	
	(void) offset;
	(void) fi;

	if (strcmp(path, "/") != 0)
		return -ENOENT;

	filler(buf, ".", NULL, 0);
	filler(buf, "..", NULL, 0);

	int i;
	for(i = 0; i < TABLE_SIZE; i++) 
		filler(buf, paths[i] + 1, NULL, 0);
	

	return 0;
}

static int hello_open(const char *path, struct fuse_file_info *fi)
{

	printf("\t\t\topen with path %s\n",path);
	fi = fi;

	// No match	
	if (compareFile(path,paths) == 0)
		return -ENOENT;

	if ((fi->flags & 3) != O_RDONLY)
		return -EACCES;
	

	return 0;
}

static int hello_read(const char *path, char *buf, size_t size, off_t offset,
		      struct fuse_file_info *fi)
{

	printf("\t\t\tread with path %s\n",path);

	size_t len;
	(void) fi;
	if(compareFile(path,paths) == 0)
		return -ENOENT;

	const char *path_str;
	path_str = returnMatch(path,paths,strings);

	len = strlen(path_str);
	if (offset < len) {
		if (offset + size > len)
			size = len - offset;
		memcpy(buf, path_str + offset, size);
		
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
	initializeFS(paths,strings);
	return fuse_main(argc, argv, &hello_oper, NULL);
}


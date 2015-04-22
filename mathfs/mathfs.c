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

const char *paths[TABLE_SIZE] = { "/add", "/sub", "/mul", "/div", "/exp", "/factor", "/fib" };
static const char *hello_str = "Hello World!\n";

// FUSE function implementations.
static int mathfs_getattr( const char *path, struct stat *stbuf )
{
	printf(MAKE_RED"\t\tgetattr with path (\"%s\")"RESET_FORMAT,path);
	printf("\n");
	int res = 0;
	int argCount = 0;
	int i = 0;

	memset( stbuf, 0, sizeof( struct stat ) );

	/*
	*	if 			root path
	*	else if 	operation directory
	*	else if 	doc path
	*	else if 	math path with arguments
	*	else 		invalid
	* */
	if ( strcmp(path, "/") == 0 )
	{
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
	}
	else if( is_dir( path ) ) 
	{
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
		stbuf->st_size = strlen(path);
	} 
	else if( is_path( path ) )
	{
		char *tempToken, *arg1, *arg2, *operation;
		char returnValue[ MAX_PATH_LEN ];

		tempToken = malloc( strlen( path ) + 1 );
		strcpy( tempToken, path );
		tempToken[strlen( path ) + 1] = '\0';
		tempToken = strtok( tempToken, "/" );

		for( i = 0; i < MAX_PATH_LEN; i ++ )
		{
			returnValue[i] = '\0';
		}

		operation = malloc( strlen( tempToken ) + 1 );
		strcpy( operation, tempToken );

		arg1 = malloc( strlen( path ) + 1 );
		arg2 = malloc( strlen( path ) + 1 );

		while( tempToken != NULL )
		{
			//printf(MAKE_YELLOW"\t\ttoken: (\"%s\")"RESET_FORMAT, tempToken);
			if(argCount == 1)
			{
				strcpy( arg1, tempToken );
			}
			else if(argCount == 2)
			{
				strcpy( arg2, tempToken );
			}
	
			tempToken = strtok( NULL, "/" );
			argCount++;
		}

		/*
		*	count = 1 		math/add
		*	count = 2 		math/add/1
		*	count = 3 		math/add/1/2
		*/
		if( argCount == 2 )
		{
			if( strcmp( arg1, "doc" ) == 0 )
			{
				stbuf->st_mode = S_IFREG | 0444;
				stbuf->st_nlink = 1;
				strcpy( returnValue, get_doc_str( operation ) );
				stbuf->st_size = strlen( returnValue );
			}
			else if( is_num( arg1 ) == 1 )
			{
				if( (strcmp( operation, "fib" ) == 0) || (strcmp( operation, "factor" ) == 0) )
				{
					stbuf->st_mode = S_IFREG | 0444;
					stbuf->st_nlink = 1;	
					strcpy( returnValue, mathOperation( operation, arg1, arg2 ) );
					stbuf->st_size = strlen( returnValue );				
				}
				else
				{
					stbuf->st_mode = S_IFDIR | 0755;
					stbuf->st_nlink = 2;
					stbuf->st_size = strlen( path );
				}
			}
			else
			{
				res = -ENOENT;
			}
		}
		else if( argCount == 3 )
		{
			if( (strcmp( operation, "fib" ) != 0) && (strcmp( operation, "factor" ) != 0) )
			{
				if( (is_num( arg1 ) == 1) && (is_num( arg2 ) == 1) )
				{
					stbuf->st_mode = S_IFREG | 0444;
					stbuf->st_nlink = 1;
					strcpy( returnValue, mathOperation( operation, arg1, arg2 ) );
					stbuf->st_size = strlen( returnValue );
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
		}
		else
		{
			res = -ENOENT;
		}

		FREE( tempToken );
		FREE( arg1 );
		FREE( arg2 );
		FREE( operation );
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
	//printf(MAKE_BLUE"\t\treaddir with path (\"%s\")"RESET_FORMAT,path);
	
	(void) offset;
	(void) fi;

	filler( buf, ".", NULL, 0 );
	filler( buf, "..", NULL, 0 );

	if (strcmp( path, "/" ) == 0 )
	{
		int i;
		for( i = 0; i < TABLE_SIZE; i++ )
		{
			filler( buf, paths[i] + 1, NULL, 0 );
		}
	}
	else if( is_dir( path ) )
	{
		const char *newString = "/doc";		
		filler( buf, newString + 1, NULL, 0 );
	}
	else
	{
		return -ENOENT;
	}
	
	return 0;
}		

static int mathfs_open( const char *path, struct fuse_file_info *fi )
{
	//printf(MAKE_GREEN"\t\topen with path (\"%s\")"RESET_FORMAT,path);

	fi = fi;

	int argCount = 0;
	char *tempToken, *operation, *arg1, *arg2;
	boolean valid = false;

	tempToken = malloc( strlen( path ) + 1 );
	strcpy( tempToken, path );
	tempToken[strlen( path ) + 1] = '\0';
	tempToken = strtok( tempToken, "/" );

	operation = malloc( strlen( tempToken ) + 1 );
	strcpy( operation, tempToken );

	arg1 = malloc( strlen( path ) + 1 );
	arg2 = malloc( strlen( path ) + 1 );

	while( tempToken != NULL )
	{
		if(argCount == 1)
		{
			strcpy( arg1, tempToken );
		}
		else if( argCount == 2 )
		{
			strcpy( arg2, tempToken );
		}
		argCount++;

		tempToken = strtok( NULL, "/" );
	}
	if( argCount == 2 )
	{
		if( strcmp( arg1, "doc" ) == 0 )
		{
			valid = true;
		}
		if( (strcmp( operation, "fib" ) == 0) || (strcmp( operation, "factor" ) == 0) )
		{
			valid = true;
		}
	}
	if( argCount == 3 )
	{
		if( (strcmp( operation, "fib" ) != 0) && (strcmp( operation, "factor" ) != 0) )
		{
			valid = true;
		}
	}

	FREE( tempToken );
	FREE( arg1 );
	FREE( arg2 );
	FREE( operation );

	// No match
	if ( valid == false )
	{
		return -ENOENT;
	}
	if ((fi->flags & 3) != O_RDONLY)
	{
		return -EACCES;
	}
	return 0;
}

static int mathfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
	//printf(MAKE_PURPLE"\t\tread with path (\"%s\")"RESET_FORMAT,path);

	size_t len;
	(void) fi;

	// No match to any math function
	if ( is_dir( path ) != 0 )
	{
		return -ENOENT;
	}

	int i = 0;
	char *tempToken, *operation, *arg1, *arg2; 
	char docStr[ MAX_PATH_LEN ];

	tempToken = malloc( strlen( path ) + 1 );
	strcpy( tempToken, path );
	tempToken[strlen( path ) + 1] = '\0';
	tempToken = strtok( tempToken, "/" );

	for( i = 0; i < MAX_PATH_LEN; i ++ )
	{
		docStr[i] = '\0';
	}

	operation = malloc( strlen( tempToken ) + 1 );
	strcpy( operation, tempToken );

	arg1 = malloc( strlen( path ) + 1 );
	arg2 = malloc( strlen( path ) + 1 );


	int argCount = 0;

	while( tempToken != NULL )
	{
		if( argCount == 1 )
		{
			strcpy( arg1, tempToken );
		}
		else if( argCount == 2 )
		{
			strcpy( arg2, tempToken );
		}
		argCount++;

		tempToken = strtok( NULL, "/" );
	}
	if( argCount == 2 )
	{
		if( strcmp( arg1, "doc" ) == 0 )
		{
			strcpy( docStr, get_doc_str(operation) );
		}
		if( (strcmp( operation, "fib" ) == 0) || (strcmp( operation, "factor" ) == 0) )
		{
			strcpy( docStr, mathOperation( operation, arg1, arg2 ) );
		}

	}
	else if( argCount == 3 )
	{
		if( (strcmp( operation, "fib" ) != 0) && (strcmp( operation, "factor" ) != 0) )
		{
			strcpy( docStr, mathOperation( operation, arg1, arg2 ) );
		}
	}
	else
	{
		FREE( tempToken );
		FREE( arg1) ;
		FREE( arg2 );
		FREE( operation );
		return -ENOENT;
	}

	len = strlen( docStr );

	FREE( tempToken );
	FREE( arg1 );
	FREE( arg2 );
	FREE( operation );

	if ( offset < len )
	{
		if ( offset + size > len )
		{
			size = len - offset;
		}
		memcpy( buf, docStr + offset, size );
	} 
	else
	{
		size = 0;
	}
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
    return fuse_main(argc, argv, &mathfs_oper, NULL);
}
#include "defs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

const char *pathfs[TABLE_SIZE] = { "add", "sub", "mul", "div", "exp", "factor", "fib" };
const char *dirPaths[TABLE_SIZE] = { "/add", "/sub", "/mul", "/div", "/exp", "/factor", "/fib" };
const char *docsPaths[TABLE_SIZE] =
{
	"Add two numbers.\nThe file add/a/b contains the sum a+b\n",									/* 1 */
	"Subtract two numbers.\nThe file sub/a/b contains the difference a-b.\n",						/* 2 */
	"Multiply two numbers.\nThe file mul/a/b contains the product a*b.\n",							/* 3 */
	"Divide two numbers.\nThe file fiv/a/b contains the quotient of a/b.\n",						/* 4 */
	"Raise a number to an exponent.\nThe file exp/a/b contains a raised to the power of b.\n",		/* 5 */
	"Show the prime factors of a number.\nThe file factor/n contains the prime factors of n.\n",	/* 6 */
	"The file fib/n contains the first n fibonacci numbers.\n",										/* 7 */
};

/* Returns 1 if the string is a valid number, integer or decimal */
int is_num( const char *path )
{
	int ch = 0;
	int dotCount = 0;

	if( path[0] == '-' && strlen(path) > 1 )
	{
		ch++;
	}

	for( ; ch<strlen(path); ch++)
	{
		if(isdigit(path[ch]) != 0 )
		{
			//printf("\n\tchar: %c\n", path[ch]);
		}
		else if( path[ch] == '.' )
		{
			dotCount++;
		}
		else
		{
			return 0;
		}
	}

	if(dotCount > 1)
	{
		return 0;
	}
	return 1;
	/*
	char *endPtr;
	double a = strtod( path, &endPtr );
	int hack;
	if( (a/10) > strlen(endPtr) )
	{
		hack = strlen(path);
	}
	else
	{
		hack = strlen(endPtr);
	}

	if( strncmp( path, endPtr, hack ) != 0 )
	{
		//printf("\npath: %s\nendptr: %s\n");
		return 1;
	}
	return 0;
	*/
}

/* returns the doc description for a corresponding path*/
char* get_doc_str( const char *path )
{
	int i;

	for( i = 0; i < TABLE_SIZE; i++ )
	{
		if( strcmp( path, pathfs[i] ) == 0 )
		{
			return (char*)( docsPaths[i] );
		}
	}
	return "\0";
}

/* returns the index number of a given path */
int get_index( const char *path )
{
	int i;
	for( i = 0; i < TABLE_SIZE; i++ )
	{
		if( strcmp( path, pathfs[i] ) == 0 )
		{
			return i;
		}
	}
	return -1;	
}

/* checks if file is one of the math operation directories */
int is_dir( const char *path )
{
	int i;
	for( i = 0; i < TABLE_SIZE; i++ )
	{
		if( strcmp( path, dirPaths[i] ) == 0 )
		{
			return 1;
		}
	}
	return 0;
}

/* checks if the file's path starts with one of the math operation directories*/
int is_path( const char *path )
{	
	int i;
	for( i = 0; i < TABLE_SIZE; i++ )
	{
		if( strncmp( path, dirPaths[i], strlen(dirPaths[i]) ) == 0 )
			return 1;
	}
	return 0;
}

/* returns 1 if the string is in docPaths */
int is_doc( const char *path ) 
{
	int i;
	for( i = 0; i < TABLE_SIZE; i++ ) 
	{
		if( strcmp( path,docsPaths[i] ) == 0 )
		{
			return 1;
		}
	}
	return 0;
}
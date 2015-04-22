#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* finds the prime factors of a number */
char* my_factor( char* arg1, char* arg2 )
{
	long int a = strtod( arg1, NULL );

	int ch = 0;
	if( arg1[0] == '-' && strlen(arg1) > 1 )
	{
		ch++;
	}

	for( ; ch<strlen(arg1); ch++)
	{
		if(isdigit(arg1[ch]) == 0)
		{
			return "Error: Fib requires an integer input\n";
		}
	}

	int i;
	static char toReturn[ MAX_PATH_LEN ];
	for( i = 0; i < MAX_PATH_LEN; i++ )
	{
		toReturn[i] = '\0';
	}


	if( a == 1 )
	{
		char* addPart = (char*)malloc( sizeof(char)*MAX_PATH_LEN );
		sprintf( addPart, "%d\n", 1 );
		strcat( toReturn, addPart );
		FREE( addPart );

		return toReturn;
	}

	if( a < 0 )
	{
		char* addPart = (char*)malloc( sizeof(char)*MAX_PATH_LEN );
		sprintf( addPart, "%d\n", -1 );
		strcat( toReturn, addPart );
		FREE( addPart );
		a = a * -1;
	}

	while ( a % 2 == 0 )
	{
		char* addPart = (char*)malloc( sizeof(char)*MAX_PATH_LEN );
		sprintf( addPart, "%d\n", 2 );
		strcat( toReturn, addPart );
		a = a / 2;
		FREE( addPart );
	}
	for ( i = 3; i <= sqrt( a ); i = i + 2 )
	{
		char* addPart = (char*)malloc( sizeof(char)*MAX_PATH_LEN );
		while ( a % i == 0 )
		{
			sprintf( addPart, "%d\n", i );
			strcat( toReturn, addPart );
			a = a / i;
		}
		FREE( addPart );
	}
	if ( a > 2 )
	{
		char* addPart = (char*)malloc( sizeof(char)*MAX_PATH_LEN );
		sprintf( addPart, "%d\n", a );
		strcat( toReturn, addPart );
		FREE( addPart );
	} 
	return toReturn;
}

/* returns every integer up to a specified amount */
char* my_fib( char* arg1, char* arg2 )
{
	int ch;
	for(ch = 0; ch<strlen(arg1); ch++)
	{
		if(isdigit(arg1[ch]) == 0)
		{
			return "Error: Fib requires an integer input\n";
		}
	}

	int i = 0;
	static char toReturn[ MAX_PATH_LEN ];

	for( i = 0; i < MAX_PATH_LEN; i++ )
	{
		toReturn[i] = '\0';
	}

	long unsigned int n = atoi( arg1 );
	long unsigned int a = 0, b = 1, c;

	if( n == 0 )
	{
		sprintf( toReturn, "%d\n", 0 );
		return toReturn;
	}
	char* addPart = (char*)malloc( sizeof(char)*MAX_PATH_LEN );
	sprintf( addPart, "%d\n", 0 );
	strcat( toReturn, addPart );
	FREE( addPart );

	if( n == 1 )
	{
		a = 1;
		char* addPart = (char*)malloc( sizeof(char)*MAX_PATH_LEN );
		sprintf( addPart, "%lu\n", a );
		strcat( toReturn, addPart );
		FREE( addPart );

		return toReturn;
	}

	strcat(toReturn, "1\n");

	for( i = 2; i <= n; i++ )
	{
		c = a + b;
		if( (c < b) || (c < a) )
		{
			strcat( toReturn, "Overflow - input too large\n" );
			return toReturn;
		}
		else
		{
			char* addPart = (char*)malloc( sizeof(char)*MAX_PATH_LEN );
			sprintf( addPart, "%lu\n", c );
			strcat( toReturn, addPart );
			FREE( addPart );
		}
		a = b;
		b = c;
	}
	return toReturn;
}

/* adds two numbers */
char* my_add( char* arg1, char* arg2 )
{
	int i = 0;
	static char toReturn[ MAX_PATH_LEN ];

	for( i = 0; i < MAX_PATH_LEN; i++ )
	{
		toReturn[i] = '\0';
	}

	double a = strtod( arg1, NULL);
	double b = strtod( arg2, NULL);
	double c = a + b;
	snprintf( toReturn, MAX_PATH_LEN, "%f\n", c );

	return toReturn;
}

/* subtracts two numbers */
char* my_sub( char* arg1, char* arg2 )
{
	int i = 0;
	static char toReturn[ MAX_PATH_LEN ];
	for( i = 0; i < MAX_PATH_LEN; i++ )
	{
		toReturn[i] = '\0';
	}
	double a = strtod( arg1, NULL);
	double b = strtod( arg2, NULL);
	double c = a - b;
	snprintf( toReturn, MAX_PATH_LEN, "%f\n", c );

	return toReturn;
}

/* multiplies two numbers */
char* my_mul( char* arg1, char* arg2 )
{
	int i = 0;
	static char toReturn[ MAX_PATH_LEN ];
	for( i = 0; i < MAX_PATH_LEN; i++ )
	{
		toReturn[i] = '\0';
	}
	double a = strtod( arg1, NULL);
	double b = strtod( arg2, NULL);
	double c = a * b;
	snprintf( toReturn, MAX_PATH_LEN, "%f\n", c );

	return toReturn;
}

/* divides two numbers */
char* my_div( char* arg1, char* arg2 )
{
	int i = 0;
	static char toReturn[ MAX_PATH_LEN ];
	for( i = 0; i < MAX_PATH_LEN; i++ )
	{
		toReturn[i] = '\0';
	}
	double a = strtod( arg1, NULL);
	double b = strtod( arg2, NULL);

	if( b == 0 )
	{
		return "Error: Trying to divide by zero\n";
	}
	double c = a / b;
	snprintf( toReturn, MAX_PATH_LEN, "%f\n", c );

	return toReturn;
}

/* returns the value of arg1 raised to the power of arg2 */
char* my_exp( char* arg1, char* arg2 )
{
	int i = 0;
	static char toReturn[ MAX_PATH_LEN ];
	for( i = 0; i < MAX_PATH_LEN; i++ )
	{
		toReturn[i] = '\0';
	}
	double a = strtod( arg1, NULL);
	double b = strtod( arg2, NULL);
	double c = pow( a, b );
	snprintf( toReturn, MAX_PATH_LEN, "%f\n", c );

	return toReturn;
}

/* determines the appropriate math operation, and calls the according function pointer */
char* mathOperation( char* operation, char* arg1, char* arg2 )
{
	f_ptr f_ptr_array[ TABLE_SIZE ] = { my_add, my_sub, my_mul, my_div, my_exp, my_factor, my_fib };

	int index = get_index( operation );
	static char toReturn[ MAX_PATH_LEN ];

	if( index < TABLE_SIZE && index >= 0 )
	{
		strcpy( toReturn, f_ptr_array[index]( arg1, arg2 ) );
	}
	return toReturn;
}
#ifndef HEADERS_H
#define HEADERS_H

/* Terminal Text Format Macros */
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

/* type declarations */
typedef enum {
	false,
	true
} boolean;
#define TABLE_SIZE 7
#define MAX_PATH_LEN 2048

/* Free Macro, Sets pointer to null */
#define FREE(ptr) \
	do{ \
		free((ptr)); \
		(ptr)=NULL; \
	}while(0) 

/* mathdefs.c */
typedef char* (*f_ptr)( char* arg1, char* arg2 );
char* my_factor( char* arg1, char* arg2 );
char* my_fib( char* arg1, char* arg2 );
char* my_add( char* arg1, char* arg2 );
char* my_sub( char* arg1, char* arg2 );
char* my_mul( char* arg1, char* arg2 );
char* my_div( char* arg1, char* arg2 );
char* my_exp( char* arg1, char* arg2 );
char* mathOperation( char* operation, char* arg1, char* arg2 );

/* util.c */
int is_num( const char *path );
int is_doc(const char *path );
int is_dir( const char *path );
int is_path( const char *path );
int get_index( const char *path );
char* get_doc_str( const char *path );

#endif
#ifndef MARKOV_TEXT_ERROR
#define MARKOV_TEXT_ERROR

#include <stdlib.h>
#include <stdio.h>


#define MALLOC_RETURN_CHECK(pointer) { if( (pointer) == NULL) {		\
					       fatal_error(err_malloc); } }

enum error_index
{
	err_no_arguments = 0,
	err_file_open,
	err_file_read,
	err_file_name_length,
	err_malloc
};

#ifndef NUM_ERROR_MESSAGES

#define NUM_ERROR_MESSAGES 5
extern const int error_code_extra_args[];

extern const char * const error_messages[NUM_ERROR_MESSAGES];
#endif


__attribute__((noreturn)) void fatal_error( int );

#endif

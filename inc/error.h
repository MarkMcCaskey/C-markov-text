#ifndef MARKOV_TEXT_ERROR
#define MARKOV_TEXT_ERROR

#include <stdlib.h>
#include <stdio.h>

#define NUM_ERROR_MESSAGES 5

#define MALLOC_RETURN_CHECK(pointer) (if( (pointer) == NULL) {	\
					      fatal_error(err_malloc); })

enum error_index
{
	err_no_arguments = 0,
	err_file_open,
	err_file_read,
	err_file_name_length,
	err_malloc
};

const int error_code_extra_args[] = {0, 1, 1, 1, 0};

const char * const error_messages[NUM_ERROR_MESSAGES] =
{
	"pass one or more file names to the program to run it",
	"the file %s could not be opened",
	"the file %s could not be read",
	"the file %s's length is too long to be opened",
	"memory could not be allocated"
};


__attribute__((noreturn)) void fatal_error( int );

#endif

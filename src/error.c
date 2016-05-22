#include <stdio.h>

#define NUM_ERROR_MESSAGES 5

const int error_code_extra_args[] = {0, 1, 1, 1, 0};

const char * const error_messages[NUM_ERROR_MESSAGES] =
{
	"pass one or more file names to the program to run it",
	"the file %s could not be opened",
	"the file %s could not be read",
	"the file %s's length is too long to be opened",
	"memory could not be allocated"
};

#include "../inc/error.h"


__attribute__ ((noreturn))
void fatal_error( int error_number )
{
	fprintf( stderr, "Error: " );

	if( error_code_extra_args[error_number] )
	{
		//char* str = va_arg( ap, char* );
		fprintf( stderr, error_messages[error_number], "TEMP FILLER STRING" );
	} else { fprintf( stderr, error_messages[error_number] ); }


	fprintf( stderr, "\n" );
	exit( EXIT_FAILURE );
}

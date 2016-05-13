#include "error.h"

__attribute__ ((noreturn))
void fatal_error( int error_number )
{
	fprintf( stderr, "Error: " );

	if( error_code_extra_args[error_number] )
	{
		char* str = va_arg( ap, char* );
		fprintf( stderr, error_messages[error_number], str );
	} else { fprintf( stderr, error_messages[error_number] ); }


	fprintf( stderr, "\n" );
	exit( EXIT_FAILURE );
}

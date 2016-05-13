#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prefixtree.h"
#include "error.h"

#define FILE_NAME_MAX_SIZE 64
#define WORD_MAX_LENGTH 32
#define FILE_CHUNK_SIZE 2048

char file_name[FILE_NAME_MAX_SIZE];

int main(char**, int);

extern word global_last_word; //prefixtree.h
prefix_tree global_prefix_tree = { NULL, NULL };

int main( char** argv, int argc )
{
	FILE* input_file;
	char file_contents[FILE_CHUNK_SIZE];
	char word[WORD_MAX_LENGTH] = {};

	/*
	 * Open file and handle errors
	 */
	
	if( argc < 2 ) { fatal_error( err_no_arguments ); }
	
	strncpy( file_name, argv[1], FILE_NAME_MAX_SIZE );
	if( file_name[FILE_NAME_MAX_SIZE - 1] != 0 )
	{ fatal_error(err_file_name_length); }
	
	input_file = fopen( argv[1] );
	
	if( input_file == NULL ) { fatal_error( err_file_open ); }
	
	if( fgets( file_contents, FILE_CHUNK_SIZE, input_file ) == NULL )
	{ fatal_error( err_file_read ); }


	/*
	 * Build global_prefix_tree from the input file
	 */


	int j = 0; //index of file contents
	while( file_contents[j] != EOF ) {
		for( int i = 0; i < WORD_MAX_LENGTH; ++i )
		{
			if( file_contents[j] == ' '  ||
			    file_contents[j] == '\t' ||
			    file_contents[j] == ','  ||
			    file_contents[j] == '.'  ||
			    file_contents[j] == '?'  ||
			    file_contents[j] == '!' )
			{ j++; word[i] = 0; break; }
			else if( file_contents[j] == 0 ) 
			{ goto file_ended; }

			word[i] = file_contents[j];
			j++;
		}

		update_prefix_tree( &global_prefix_tree, word );

		if( j >= FILE_CHUNK_SIZE )
		{
			//get new chunk 
			if( fgets(file_contents,
				  FILE_CHUNK_SIZE,
				  input_file)
			    == NULL )
			{
				/*
				 * fgets doesn't make a distinction between
				 * read errors and EOF with nothing read.
				 * Assume that return of NULL after a 
				 * successful read means file ended.
				 */
			file_ended:
				break;
			}
		}
	}


	/*
	 * Generate new text based on global_prefix_tree
	 */
		
	
	//free global_prefix_tree
	fclose( input_file );
	exit( EXIT_SUCCESS );
}

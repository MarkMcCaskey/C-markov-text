#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../inc/prefixtree.h"
#include "../inc/error.h"
#include "../inc/generate.h"

#define FILE_NAME_MAX_SIZE 64
#define NUMBER_SENTENCES_TO_GENERATE 10

char file_name[FILE_NAME_MAX_SIZE];

int main(int, char**);

extern word* global_last_word; //prefixtree.h
prefix_tree* global_prefix_tree;

int main( int argc, char** argv )
{
	FILE* input_file;
        srandom(time(NULL));

	/*
	 * Open file and handle errors
	 */
	
	if( argc < 2 ) { fatal_error( err_no_arguments ); }
	
	strncpy( file_name, argv[1], FILE_NAME_MAX_SIZE );
	if( file_name[FILE_NAME_MAX_SIZE - 1] != 0 )
	{ fatal_error(err_file_name_length); }
	
	input_file = fopen( argv[1], "r" );
	
	if( input_file == NULL ) { fatal_error( err_file_open ); }
	

	/*
	 * Build global_prefix_tree from the input file
	 */

        global_prefix_tree = build_prefix_tree(input_file);


	/*
	 * Generate new text based on global_prefix_tree
	 */

        generate_text(NUMBER_SENTENCES_TO_GENERATE, global_prefix_tree);
		
	
	//free global_prefix_tree
	fclose( input_file );
	exit( EXIT_SUCCESS );
}

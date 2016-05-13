#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../inc/prefixtree.h"
#include "../inc/error.h"

#define FILE_NAME_MAX_SIZE 64
#define WORD_MAX_LENGTH 32
#define FILE_CHUNK_SIZE 2048
#define NUMBER_SENTENCES_TO_GENERATE 10

char file_name[FILE_NAME_MAX_SIZE];

int main(int, char**);

extern word global_last_word; //prefixtree.h
prefix_tree global_prefix_tree;

int main( int argc, char** argv )
{
	FILE* input_file;
	char file_contents[FILE_CHUNK_SIZE];
	char word[WORD_MAX_LENGTH] /*= {}*/;
	srandom(time(NULL)); //random seed based on time

	/*
	 * Open file and handle errors
	 */
	
	if( argc < 2 ) { fatal_error( err_no_arguments ); }
	
	strncpy( file_name, argv[1], FILE_NAME_MAX_SIZE );
	if( file_name[FILE_NAME_MAX_SIZE - 1] != 0 )
	{ fatal_error(err_file_name_length); }
	
	input_file = fopen( argv[1], "r" );
	
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
			    file_contents[j] == ',')
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
	//TODO: modify prefix tree to include sentence endings
	//also consider adding a start symbol for multiple texts


	//TODO: capitilization was never covered, fix this later

	
	int number_sentences = 0;

	//until start symbol implemented, start each text with 'the'
	word* current_word = find_word(&global_prefix_tree, "the");
	/*** Code to be removed: ***/
	if( current_word == NULL )
	{
		fprintf(stderr, "Hack to start each text with the failed"
			"no 'the' in input text.\nexiting\n");
		exit(EXIT_FAILURE);
	}
	related_word* related_word_iter = current_word->related_words;
	int random_iter = 0;

	while( number_sentences < NUMBER_SENTENCES_TO_GENERATE )
	{
		random_iter = random() %
			(current_word->related_words_total_count);


		random_iter -= related_word_iter->count;
		while( random_iter > 0 )
		{
			random_iter -= related_word_iter->count;
			related_word_iter = related_word_iter->next;
		}
		printf("%s ", related_word_iter->self->word_text);

		//if ...->word_text is '.', '!', or '?'
		//     number_sentences++
	}
		
	
	//free global_prefix_tree
	fclose( input_file );
	exit( EXIT_SUCCESS );
}

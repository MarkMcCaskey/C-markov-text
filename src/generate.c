#include <stdlib.h>
#include <stdio.h>
#include "../inc/error.h"
#include "../inc/generate.h"


prefix_tree* build_prefix_tree(FILE* input)
{
	char file_contents[FILE_CHUNK_SIZE];
	char word[WORD_MAX_LENGTH] = {};
        prefix_tree* pt = (prefix_tree*) malloc(sizeof(prefix_tree));
        MALLOC_RETURN_CHECK(prefix_tree);

        /*pt->next_words = (prefix_tree_list*) malloc(sizeof(prefix_tree_list));
        MALLOC_RETURN_CHECK(pt->next_words);

        pt->found_word = NULL;

        pt->next_words->next = NULL;
        pt->next_words->pt = NULL;
        pt->next_words->next_char = 0;*/

	if( fgets( file_contents, FILE_CHUNK_SIZE, input ) == NULL )
	{ fatal_error( err_file_read ); }

	int j = 0; //index of file contents
	while( file_contents[j] != EOF ) {
		for( int i = 0; i < WORD_MAX_LENGTH; ++i )
		{
			if( file_contents[j] == ' '  ||
			    file_contents[j] == '\t' ||
			    file_contents[j] == ',')
			{ j++; word[i] = 0;
                                for( file_contents[j] == ' ' ||
                                             file_contents[j] == '\t' ||
                                             file_contents[j] == '\n' &&
                                             (j < WORD_MAX_LENGTH); ++j ) {} //this may need extra handling if j passes WORD_MAX_LENGTH
                                
                                           
                        }
			else if( file_contents[j] == 0 ) 
			{ goto file_ended; }

			word[i] = file_contents[j];
			j++;
		}

		update_prefix_tree( pt, word );

		if( j >= FILE_CHUNK_SIZE )
		{
			//get new chunk 
			if( fgets(file_contents,
				  FILE_CHUNK_SIZE,
				  input)
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
        return pt;
}

char* generate_text(int number_of_sentences, prefix_tree* pt)
{
        char* output = (char*) malloc(sizeof(char) * TEXT_CHUNK_SIZE );
        int output_counter = 0;
        int output_multiplier = 1;
        MALLOC_RETURN_CHECK(output);
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

	while( number_sentences < number_of_sentences )
	{
		random_iter = random() %
			(current_word->related_words_total_count);


		random_iter -= related_word_iter->count;
		while( random_iter > 0 )
		{
			random_iter -= related_word_iter->count;
			related_word_iter = related_word_iter->next;
		}

                output_counter += strlen(related_word_iter->self->word_text) + 1;
                if( output_counter > (output_multiplier * TEXT_CHUNK_SIZE ) )
                        {
                                output_multiplier++;
                                realloc( output,
                                         (output_multiplier * TEXT_CHUNK_SIZE) );
                                MALLOC_RETURN_CHECK( output );
                        }
                
                sprintf((output + (output_multiplier * TEXT_CHUNK_SIZE) + output_counter), "%s ", related_word_iter->self->word_text);
                
		//if ...->word_text is '.', '!', or '?'
		//     number_sentences++
        }
}

#include "../inc/prefixtree.h"
#include "../inc/error.h"

#include <assert.h>

void update_prefix_tree( prefix_tree* pt, char* new_word )
{
	assert(pt);
	assert(new_word);

	prefix_tree* pf_search = pt;
	prefix_tree_list* pfl_search = pt->next_words;
	
	int is_a_new_word = 0;

	for( int i = 0; i < strlen( new_word ); ++i )
	{
		if( is_a_new_word )
		{
			assert(pf_search);

			pf_search->next_words = (prefix_tree_list*)
				malloc(sizeof(prefix_tree_list));
			MALLOC_RETURN_CHECK(pf_search->next_words);

			pfl_search = pf_search->next_words;
			pfl_search->next = NULL;
			pfl_search->pt = (prefix_tree*)
				malloc(sizeof(prefix_tree));
			MALLOC_RETURN_CHECK(pfl_search->pt);

			pfl_search->next_char = new_word[i];
			pf_search = pfl_search->pt;
			pf_search->next_words = NULL;
			pf_search->word = NULL;

			continue;
		}

		
		while(pfl_search)
		{
			if(pfl_search->next_char == new_word[i])
			{
				pf_search = pfl_search->pt;
				goto next_letter_found;
			}

			if( pfl_search->next )
			{ pfl_search = pfl_search->next; }
			else { break; }
		}
		//next letter was not found
		is_a_new_word = 1;

		pfl_search->next = (prefix_tree_list*)
			malloc(sizeof( prefix_tree_list ));
		MALLOC_RETURN_CHECK(pfl_search->next);

		pfl_search->next->next = NULL;
		pfl_search->next->pt = (prefix_tree*)
			malloc(sizeof( prefix_tree )); 
		MALLOC_RETURN_CHECK(pfl_search->next->pt);
		
		pfl_search->next->next_char = new_word[i];

		pf_search = pfl_search->next->pt;
		pfl_search = pf_search->next_words = NULL;
		pf_search->found_word = NULL;
		continue;



	next_letter_found:
		pfl_search = pf_search->next_words;
		continue;
	}

	if( is_a_new_word )
	{
		//create new word
		pf_search->word = (word*) malloc(sizeof(word));
		MALLOC_RETURN_CHECK(pf_search_>word);

		pf_search->word = {0, 0, NULL, NULL}
		pf_search->word->word_text = (char*)
			malloc(sizeof(char) * (strlen(word)));
		MALLOC_RETURN_CHECK(pf_search->word->word_text);

		strcpy(pf_search->word->word_text, word);

		//Now add this new word to the related words of the last
		//word

		if( global_last_word->related_words == NULL )
		{
			global_last_word->related_words = (related_word*)
				malloc(sizeof(related_word));
			MALLOC_RETURN_CHECK(
				global_last_word->related_words);

			global_last_word->related_words->self=
				pf_search->word;
			global_last_word->related_words->next = NULL;
			global_last_word->related_words->count = 1;

			global_last_word->number_related_words = 1;
			global_last_word->related_words_total_count = 1;

			global_last_word = pf_search->word;
			return;
		}
		//else at least one other related word
		related_word* temp = global_last_word->related_words;
		
		global_last_word->related_words = (related_word*)
			malloc(sizeof(related_word));
		MALLOC_RETURN_CHECK(global_last_word->related_words);
		
		global_last_word->related_words->count = 0;
		global_last_word->self = pf_search->word;
		global_last_word->next = temp;
		
		global_last_word->number_related_words += 1;
		global_last_word->related_words_total_count += 1;
		
		global_last_word = pf_search->word;
		return;
	}
	
	//otherwise word was found

	related_word* word_search = global_last_word->related_word_list;
	if( word_search == NULL )
	{
		global_last_word->related_words = (related_word*)
			malloc(sizeof( related_word ));
		MALLOC_RETURN_CHECK(global_last_word->related_words);

		global_last_word->related_words->count = 1;
		global_last_word->related_words->self =
			pf_search->found_word;
		global_last_word->related_words->next = NULL;

		global_last_word->number_related_words = 1;
		global_last_word->related_words_total_count = 1;
		
		global_last_word = pf_search->found_word;

		return;
	}

	while(word_search)
	{
		if( strcmp( word_search->self->word_text, new_word ) == 0 )
		{
			word_search->count += 1;
			global_last_word->related_words_total_count += 1;

			break;
		}

		if( word_search->next == NULL )
		{
			word_search->next = (related_word*)
				malloc(sizeof( related_word ));
			word_search->next->next = NULL;
			word_search->next->count = 1;
			word_search->next->self = pf_search->found_word;

			global_last_word->related_words_total_count += 1;
			global_last_word->number_related_words += 1;

			break;
		}
	}

	global_last_word = pf_search->found_word;
	return;
}

__attribute__ ((pure))
word* find_word( prefix_tree* pt, char* word )
{
	assert(pt);
	assert(word);

	prefix_tree_list* ptl_search = pt->next_words;
	assert(prefix_tree_list);
	
	for( int i = 0; i < strlen( word ); ++i )
	{
		while( ptl_search )
		{
			if( ptl_search->next_char == word[i] )
			{
				break;
			} else if( ptl_search->next == NULL )
			{
				//The letter word[i] could not be found
				//so the word is not in the tree
				return NULL;
			}
		}

		assert(ptl_search_>pt);
		ptl_search = ptl_search->pt->next_words;
	}


	//TODO: simplify this later
	//The following branch is redundant
	//Normally returning ptl_search->pt->found_word will take care of
	//returing NULL if it's not found.  However for testing purposes
	//we want to check that the strings match
	if( ptl_search->pt->found_word == NULL )
	{
		//prefix of word found, but it's not a word in the tree
		return NULL;
	}
	
	assert(strcmp(ptl_search->pt->found_word->word_text, word) == 0);

	return ptl_search->pt->found_word;
}

#include "prefixtree.h"

#include <assert.h>

void update_prefix_tree( prefix_tree* pt, char* new_word )
{
	prefix_tree* pf_search = pt;
	prefix_tree_list* pfl_search = pt->next_words;
	
	int is_a_new_word = 0;

	for( int i = 0; i < strlength( new_word ); ++i )
	{
		if( is_a_new_word )
		{
			pf_search->next_words = (prefix_tree_list*)
				malloc(sizeof(prefix_tree_list));
			pfl_search = pf_search->next_words;
			pfl_search->next = NULL;
			pfl_search->pt = (prefix_tree*)
				malloc(sizeof(prefix_tree));
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
		pfl_search->next->next = NULL;
		pfl_search->next->pt = (prefix_tree*)
			malloc(sizeof( prefix_tree )); 
		pfl_search->next->next_char = new_word[i];

		pf_search = pfl_search->next->pt;
		pfl_search = pf_search->next_words = NULL;
		pf_search->found_word = NULL;
		continue;



	next_letter_found:

		pfl_search = pf_search->next_words;
	}

	if( is_a_new_word )
	{
		(*NULL) = "Don't let this program run until this is implemented";
		undefined;
		assert(false);
		return;
	}

	//otherwise word was found

	related_word* word_search = global_last_word->related_word_list;
	if( word_search == NULL )
	{
		global_last_word->related_word_list =
			(related_word*) malloc(sizeof( related_word ));
		global_last_word->related_word_list->count = 1;
		global_last_word->related_word_list->self =
			pf_search->found_word;
		global_last_word->related_word = NULL;
		global_last_word = pf_search->found_word;

		return;
	}

	//following code needs huge review
	while(word_search)
	{
		if( strcmp( word_search->self->word_text, new_word ) == 0 )
		{
			word_search->self->related_words_total_count += 1;
			word_search->count += 1;

			break;
		}

		if( word_search->next == NULL )
		{
			word_search->next = (related_word*)
				malloc(sizeof( related_word ));
			word_search->next->next = NULL;
			word_search->next->count = 1;
			word_search->next->self = pf_search->found_word;
			       
			word_search->self->related_words_total

			break;
		}
	}

	global_last_word = pf_search->found_word;
	return;
}

__attribute__ ((pure))
word* find_word( prefix_tree* pt, char* word )
{
	prefix_tree_list* ptl_search = pt->next_words;

	for( int i = 0; i < strlen( word ); ++i )
	{
		while( ptl_search )
		{
			
		}
	}
}

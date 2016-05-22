#include "../inc/prefixtree.h"
#include "../inc/error.h"

#include <assert.h>


/*
 * update_prefix_tree logic:
 * iterate through letters in input_word {
 *    search input_prefix_tree for word
 *    if new letter is found, build up tree to now have this new word
 *      otherwise just use the word found in the tree
 * }
 * update relationship of last_word and input_word in the prefix_tree
 * done.
 */

/* 
 * rewriting function.
 */
void update_prefix_tree_2( prefix_tree* pt, char* input_word )
{
	assert(pt);
	assert(input_word);

	prefix_tree* closest = find_closest_word(pt, input_word);
	if( closest == NULL )
	{
		//build prefix tree
	}

	if( strcmp( input_word, closest->found_word ) == 0 )
	{
		//word found, update and return
	} 
	//otherwise word was not found, insert it
	int i;
	for( i = 0; i < strlen(input_word)
		     && input_word[i] == closest->found_word[i]; ++i ) {}

	i--; //I think this is needed; TODO: review when more awake

	for( ; i < strlen(input_word); ++i )
	{
		// insertion should prboably be a function
		prefix_list* temp = closest->next_words;
		closest->next_words = new_prefix_list();
		closest->next_words->next = temp;
		closest->next_words->pt = new_prefix_tree();
		closest->next_words->next_char = input_word[i];

		closest = closest->pt;
			
	}

	closest->found_word = new_word(input_word);

	//update relationship of new word and last word


	

	global_last_word = closest->found_word;

	return;
}
//TODO: break this into subfunctions
void update_prefix_tree( prefix_tree* pt, char* input_word )
{
	assert(pt);
	assert(input_word);

	prefix_tree* pf_search = pt;
	prefix_tree_list* pfl_search = pt->next_words;
	
	int is_a_new_word = 0;

	for( int i = 0; i < strlen( input_word ); ++i )
	{
		if( is_a_new_word )
		{
			assert(pf_search);

			//pf_search->next_words = new_prefix_tree_list();
			//following code is wrong: TODO: fix
			pf_search->next_words = (prefix_tree_list*)
				malloc(sizeof(prefix_tree_list));
			MALLOC_RETURN_CHECK(pf_search->next_words);

			//maybe the following line is backwards?
			//This code is hard to follow, need to refactor
			pfl_search = pf_search->next_words;
			pfl_search->next = NULL;
			pfl_search->pt = new_prefix_tree();

			pfl_search->next_char = new_word[i];
			pf_search = pfl_search->pt;

			continue;
		}

		
		while(pfl_search)
		{
			if(pfl_search->next_char == input_word[i])
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

		/* unsure if this is correct */
		if( ! pfl_search )
		{
			pf_search->next_words = new_prefix_tree_list();
			pfl_search = pf_search->next_words;
		}

		pfl_search->next = new_prefix_tree_list();
		pfl_search->next->pt = new_prefix_tree();
		pfl_search->next->next_char = input_word[i];

		pf_search = pfl_search->next->pt;
		pfl_search = NULL; //why?
		continue;



	next_letter_found:
		pfl_search = pf_search->next_words;
		continue;
	}

	if( is_a_new_word )
	{
		//create new word
		pf_search->found_word = new_word(input_word);

		//Now add this new word to the related words of the last
		//word
		if( ! global_last_word )
		{
			/*TODO: check this:*/
			global_last_word = pf_search->found_word;
			return;
		}
		else if( global_last_word->related_words == NULL )
		{
			global_last_word->related_words = new_related_word();
			global_last_word->related_words->self=
				pf_search->found_word;
			global_last_word->related_words->count = 1;

			global_last_word->number_related_words = 1;
			global_last_word->related_words_total_count = 1;

			global_last_word = pf_search->found_word;
			return;
		}
		//else at least one other related word
		related_word* temp = global_last_word->related_words;
		
		global_last_word->related_words = new_related_word();
		global_last_word->related_words->self = pf_search->found_word;
		global_last_word->related_words->next = temp;
		
		global_last_word->number_related_words += 1;
		global_last_word->related_words_total_count += 1;
		
		global_last_word = pf_search->found_word;
		return;
	}
	
	//otherwise word was found

	related_word* word_search = global_last_word->related_words;
	if( word_search == NULL )
	{
		global_last_word->related_words = new_related_word();

		global_last_word->related_words->count = 1;
		global_last_word->related_words->self =
			pf_search->found_word;

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
			word_search->next = new_related_word();
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

__attribute__((pure))
prefix_tree* find_closest_word( prefix_tree* pt, char* word )
{
	assert(pt);
	assert(word);

	prefix_tree* last_valid_location = pt; 
	prefix_tree_list* ptl_search = pt->next_words;
	assert(ptl_search);

	for( int i = 0; i < strlen( word ); ++i )
	{
		while(ptl_search)
		{
			if( ptl_search->next_char == word[i] )
			{
				last_valid_location = ptl_search->pt;
				ptl_search = last_valid_location->next_words;
				goto letter_found;
			}
			else //letter not found
			{
				ptl_search = ptl->search->next;
			}
		}
		//letter was not found
		return last_valid_location;
		
	letter_found:
		continue;
		
	}

	return last_valid_location;
}

__attribute__ ((pure))
word* find_word( prefix_tree* pt, char* word )
{
	assert(pt);
	assert(word);

	prefix_tree_list* ptl_search = pt->next_words;
	assert(ptl_search);
	
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

		assert(ptl_search->pt);
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

related_word* new_related_word(void)
{
	related_word* ret = (related_word*) malloc(sizeof(related_word));
	MALLOC_RETURN_CHECK(ret);

	ret->count = 0;
	ret->self  = NULL;
	ret->next  = NULL;

	return ret;
}

word* new_word(char* in_word)
{
	word* ret = (word*) malloc(sizeof(word));
	MALLOC_RETURN_CHECK(ret);

	ret->number_related_words = 0;
	ret->related_words_total_count = 0;
	ret->word_text = (char*) malloc(sizeof(char) * strlen(in_word));
	MALLOC_RETURN_CHECK(ret->word_text);
	ret->related_words = NULL;

	strncpy( ret->word_text, in_word strlen(in_word) );

	return ret;
}

word* new_blank_word(void)
{
	word* ret = (word*) malloc(sizeof(word));
	MALLOC_RETURN_CHECK(ret);

	ret->number_related_words = 0;
	ret->related_words_total_count = 0;
	ret->word_text = NULL;
	ret->related_words = NULL;

	return ret;
}

prefix_tree_list* new_prefix_tree_list(void)
{
	prefix_tree_list* ret = (prefix_tree_list*) malloc(
		sizeof(prefix_tree_list));
	MALLOC_RETURN_CHECK(ret);

	ret->next = NULL;
	ret->pt   = NULL;
	char      = 0;

	return ret;
}

prefix_tree* new_prefix_tree(void)
{
	prefix_tree* ret = (prefix_tree*) malloc(sizeof(prefix_tree));
	MALLOC_RETURN_CHECK(ret);

	ret->next_words = NULL;
	ret->found_word = NULL;

	return ret;
}

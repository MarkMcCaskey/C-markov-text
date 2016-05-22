#ifndef MARKOV_TEXT_PREFIXTREE
#define MARKOV_TEXT_PREFIXTREE

#include <stdlib.h>
#include <string.h>

struct word;
struct related_word;
struct prefix_tree;
struct prefix_tree_list;

typedef struct related_word {
	int count;
	struct word* self;
	struct related_word* next;
} related_word;

typedef struct word {
	int number_related_words;
	int related_words_total_count;
	char* word_text;
	related_word* related_words;
} word;

typedef struct prefix_tree_list {
	struct prefix_tree_list* next;
	struct prefix_tree* pt;
	char next_char;
} prefix_tree_list;

typedef struct prefix_tree {
	prefix_tree_list* next_words;
	word* found_word;
} prefix_tree;

word* global_last_word;

void update_prefix_tree( prefix_tree*, char* );
__attribute__ ((pure)) word* find_word( prefix_tree*, char* );
__attribute__((pure)) prefix_tree* find_closest_word( prefix_tree*, char* );

related_word*     new_related_word(void);
word*             new_word(char*);
word*             new_blank_word(void);
prefix_tree_list* new_prefix_tree_list(void);
prefix_tree*      new_prefix_tree(void);

#endif

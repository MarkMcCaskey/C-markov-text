#ifndef MARKOV_TEXT_GENERATE
#define MARKOV_TEXT_GENERATE

#include <stdlib.h>
#include "../inc/prefixtree.h"

#define WORD_MAX_LENGTH 32
#define FILE_CHUNK_SIZE 2048
#define TEXT_CHUNK_SIZE 2048

prefix_tree* build_prefix_tree(FILE*);
char* generate_text(int, prefix_tree*);

#endif

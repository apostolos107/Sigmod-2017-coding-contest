#ifndef __TRIE__
#define __TRIE__

#include "trie_node.h"
#include "tools.h"
#include "heap.h"
#include "bloom_filter.h"

typedef struct trie{
    hash_table * children;
    signed char is_static;
}trie;


trie * init_trie();
OK_SUCCESS insert_ngram(trie * my_trie, char * ngram);

OK_SUCCESS trie_clean(trie** my_trie);
OK_SUCCESS delete_ngram(trie * my_trie, char * ngram) ;
result_of_search* search(trie* my_trie,char* the_ngram,struct heap* heap);
#endif

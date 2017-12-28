#ifndef __TRIE__
#define __TRIE__

#include "trie_node.h"
#include "tools.h"
#include "heap.h"
#include "bloom_filter.h"

#define STACK_SIZE 10
#define ADD 'A'
#define DELETE 'D'
#define QUERY 'Q'

typedef struct trie{
    hash_table * children;
    signed char is_static;
    int version;
    char last_function;
}trie;


trie * init_trie();
OK_SUCCESS insert_ngram(trie * my_trie, char * ngram);
int update_version(trie * my_trie);
void trie_compress(trie * my_trie);
OK_SUCCESS trie_clean(trie** my_trie);
OK_SUCCESS delete_ngram(trie * my_trie, char * ngram) ;
result_of_search* search(trie* my_trie, char* the_ngram, struct heap* heap, int version);
#endif

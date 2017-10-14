#ifndef __TRIE__
#define __TRIE__

#include "trie_node.h"


typedef struct trie{
    trie_node* root;
}trie;


trie_node * init_trie();
OK_SUCCESS insert_ngram(trie * my_trie, char * ngram);


// OK_SUCCESS delete_ngram(index* ind,​​...​) ;
// char* search(index* ind, ​​..);

int count_words(char * sentence);
#endif

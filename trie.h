#ifndef __trie__
#define __trie__
#include <stdio.h>

#define NUMBER_OF_CHILDREN 5

struct trie{
    trie_node* root;
}trie;


struct trie_node{
    char* word;
    char is_final;
    struct trie_node** children;
}trie_node;

#endif

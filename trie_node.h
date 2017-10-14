#ifndef __TRIE_NODE__
#define __TRIE_NODE__


#define NUMBER_OF_CHILDREN 5

typedef int OK_SUCCESS;

typedef struct trie_node{
    char* word;
    char is_final;
    int current_children;
    int max_children;
    struct trie_node** children;
}trie_node;


trie_node* create_trie_node();
OK_SUCCESS insert_ngram_to_node(trie_node * node, char * ngram);

#endif

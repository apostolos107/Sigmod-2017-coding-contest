#ifndef __TRIE_NODE__
#define __TRIE_NODE__


#define NUMBER_OF_CHILDREN 5

typedef int OK_SUCCESS;

typedef struct trie_node{
    char* word;
    char is_final;
    int current_children;
    int max_children;
    struct trie_node* children;
}trie_node;


trie_node* create_trie_node();
OK_SUCCESS insert_ngram_to_node(trie_node * node, char * ngram);
OK_SUCCESS trie_delete(trie_node* node,char* ngram);
OK_SUCCESS delete_node_child(trie_node* node,int position);

/*  binary search that returns 1 if word found and -1 if not found
    if it's not NULL contains the spot that the search stoped
    the third argument can be NULL*/
int binary_search_kid(trie_node* master_node,char* word,int* spot_ptr_arg);
OK_SUCCESS trie_node_clean(trie_node* node);
#endif

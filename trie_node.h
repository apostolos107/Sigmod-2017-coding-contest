#ifndef __TRIE_NODE__
#define __TRIE_NODE__

#include "hash_table.h"


#define NUMBER_OF_CHILDREN 5
#define YES 1
#define NO -1
#define NOT_DELETED -1

typedef int OK_SUCCESS;

typedef struct ultra_node{
    short * positions;
    short counter;
}ultra_node;

typedef struct trie_node{
    char* word;
    int a_version;
    int d_version;
    signed char is_final;
    int current_children;
    int max_children;
    struct ultra_node * compressed;
    struct trie_node* children;
}trie_node;


trie_node* create_trie_node();
void init_trie_node(trie_node * node);
OK_SUCCESS insert_ngram_to_node(trie_node * node, char * ngram);
OK_SUCCESS trie_delete(hash_table * table,char* ngram,int current_version);
OK_SUCCESS delete_node_child(trie_node* node,int position);
/*  binary search that returns 1 if word found and -1 if not found
    if it's not NULL contains the spot that the search stoped
    the third argument can be NULL*/
int binary_search_array(trie_node* array, int size, char* word, int* spot_ptr_arg);
int binary_search_kid(trie_node* master_node,char* word,int* spot_ptr_arg);
OK_SUCCESS trie_node_clean(trie_node* node);
int compress(trie_node* node);
void DFS_for_compress(trie_node * root);
int static_binary_search_array(trie_node* array, int size, char* word, int* spot_ptr_arg);

#endif

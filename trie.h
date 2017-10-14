#ifndef __trie__
#define __trie__

#define NUMBER_OF_CHILDREN 5

typedef int OK_SUCCESS;

typedef struct trie_node{
    char* word;
    char is_final;
    int current_children;
    int max_children;
    struct trie_node** children;
}trie_node;


typedef struct trie{
    trie_node* root;
}trie;


trie_node * init_trie();
trie_node* create_trie_node();

// OK_SUCCESS insert_ngram(trie my_trie, char * ngram);
// OK_SUCCESS delete_ngram(index* ind,​​...​) ;
// char* search(index* ind, ​​..);

int count_words(char * sentence);
#endif

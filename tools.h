#ifndef __TOOLS_HEADER__
#define __TOOLS_HEADER__

#include "trie/trie_node.h"
#include "heap/heap.h"
#include "bloom_filter/bloom_filter.h"

int count_words(char * s);
char * copy_string(char * s);
void error_exit(char * s);

typedef struct result_of_search{
    char* cur_word;
    int current_wrote;
    int current_size;
    int num_of_results;
} result_of_search;


typedef struct stack_node{
    struct trie_node* node;
    int position;
}stack_node;

result_of_search* new_result(int size);
void delete_result(struct result_of_search** result);
void add_to_result(struct result_of_search* result, char* the_word, char* first_word, struct heap* my_heap, struct bloom_filter* bloom);

#endif

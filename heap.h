#ifndef __HEAP__STRUCT
#define __HEAP__STRUCT
#include "heap_hash.h"
#include <pthread.h>

typedef struct heap_node {
    struct heap_node* parrent;
    struct heap_node* left;
    struct heap_node* right;
    char* content;
    int appeared;
} heap_node;

typedef struct heap{
    heap_node* root;
    struct heap_hash_table* heap_hash;
    int number_of_nodes;

    pthread_mutex_t mut_heap;
    pthread_cond_t cond_heap;
    int heap_busy;

} heap;

heap_node* create_node();//allocate memomry and return a new none
void init_heap_node(heap_node*);//init's the heap node (already allocated)
heap* heap_create();//create and initialize the heap
heap_node* heap_insert(heap* the_heap,char* word);//inserts a word or if exists increase the counter
void heap_destroy(heap** the_heap);//destroys the heap
void heap_print_top_k(heap* the_heap, int k);//prints the top k

//compare two heap nodes (returns like strcmp)
int cmp_heap_node(struct heap_node* heap_node1, struct heap_node* heap_node2);

#endif

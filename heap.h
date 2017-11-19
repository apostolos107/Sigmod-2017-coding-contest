#ifndef __HEAP__STRUCT
#define __HEAP__STRUCT

typedef struct heap_node {
    struct heap_node* parrent;
    struct heap_node* left;
    struct heap_node* right;
    char* content;
    int appeared;
} heap_node;

typedef struct heap{
    heap_node* root;
    int number_of_nodes;
} heap;

int cmp_heap_node(heap_node* heap_node1, heap_node* heap_node2);

heap* heap_create();//create and initialize the heap

heap_node* heap_insert(heap* the_heap,char* word);//inserts a word or if exists increase the counter

char* heap_get_top(heap* the_heap);//returns the most finded word

heap_node* heap_delete_top(heap* the_heap);//deletes the heap root item

heap_node* heap_destroy(heap** the_heap);//destroys the heap

heap_node* find_the_parent(heap* the_heap,int*,int) ;

#endif

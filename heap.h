typedef struct heap_node {
    heap_node* left;
    heap_node* right;
    char* content;
    int appeared;
} heap_node;

typedef struct heap{
    heap_node* root;
} heap;

heap* heap_create();//create and initialize the heap

heap_node* heap_insert(char* word);//inserts a word or if exists increase the counter

char* heap_get_top(char* word);//returns the most finded word

heap_node* heap_delete_top();//deletes the heap root item

heap_node* heap_destroy();//destroys the heap

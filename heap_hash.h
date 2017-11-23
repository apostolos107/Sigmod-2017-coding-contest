#ifndef __HEAP_HASH_TABLE__
#define __HEAP_HASH_TABLE__

#include "heap.h"
#include "tools.h"

#define HASH_START_SIZE 100
#define BUCKET_START_SIZE 20

typedef struct heap_hash_bucket{
    struct heap_node* children;
    int current_children;
    int max_children;
}heap_hash_bucket;

typedef struct heap_hash_table{
    struct heap_hash_bucket * buckets;
    int mod_value;
    int max_breaking;
    int current_breaking;
    int round;
    int size;
} heap_hash_table;

unsigned long heap_hash_word(char * str);
int heap_hash_round(unsigned long code, int mod_value);
heap_hash_table* heap_create_hash_table();
void heap_create_hash_node(heap_hash_bucket * node);
struct heap_node * heap_hash_insert(heap_hash_table* table, char * word);
struct heap_node * heap_hash_bucket_insert(heap_hash_table* table, int pos, char * word);
int heap_expand_hash_table(heap_hash_table* table);
struct heap_node * heap_hash_search(heap_hash_table* table, char * word);
int heap_hash_delete(heap_hash_table* table, char * word);
void heap_hash_clean(heap_hash_table** table);
int heap_hash_bucket_delete(heap_hash_bucket * bucket, char * word);
int heap_hash_delete(heap_hash_table* table, char * word);
int heap_binary_search_array(heap_node* array, int size, char* word, int* spot_ptr_arg);

#endif

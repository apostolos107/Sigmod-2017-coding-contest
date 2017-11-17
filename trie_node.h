#ifndef __TRIE_NODE__
#define __TRIE_NODE__



#define NUMBER_OF_CHILDREN 5
#define HASH_START_SIZE 5
#define BUCKET_START_SIZE 5


typedef int OK_SUCCESS;

typedef struct trie_node{
    char* word;
    char is_final;
    int current_children;
    int max_children;
    struct trie_node* children;
}trie_node;

typedef struct hash_bucket{
    trie_node * children;
    int current_children;
    int max_children;
}hash_bucket;

typedef struct hash_table{
    hash_bucket * buckets;
    int mod_value;
    int max_breaking;
    int current_breaking;
    int round;
    int size;
} hash_table;


trie_node* create_trie_node();
void init_trie_node(trie_node * node);
OK_SUCCESS insert_ngram_to_node(trie_node * node, char * ngram);
OK_SUCCESS trie_delete(hash_table * table,char* ngram);
OK_SUCCESS delete_node_child(trie_node* node,int position);
/*  binary search that returns 1 if word found and -1 if not found
    if it's not NULL contains the spot that the search stoped
    the third argument can be NULL*/
int binary_search_array(trie_node* array, int size, char* word, int* spot_ptr_arg);
int binary_search_kid(trie_node* master_node,char* word,int* spot_ptr_arg);
OK_SUCCESS trie_node_clean(trie_node* node);

unsigned long hash_word(char * str);
int hash_round(unsigned long code, int mod_value);
hash_table * create_hash_table();
void create_hash_node(hash_bucket * node);
trie_node  * hash_insert(hash_table * table, char * word);
trie_node  * hash_bucket_insert(hash_table * table, int pos, char * word);
int expand_hash_table(hash_table * table);
trie_node  * hash_search(hash_table * table, char * word);
int hash_delete(hash_table * table, char * word);
void hash_clean(hash_table ** table);
int hash_bucket_delete(hash_bucket * bucket, char * word);
int hash_delete(hash_table * table, char * word);

#endif

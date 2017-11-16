#ifndef __HASH_TABLE_HEADER__
#define __HASH_TABLE_HEADER__

#include "trie_node.h"

#define HASH_START_SIZE 5
#define BUCKET_START_SIZE 5

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

unsigned long hash_word(char * str);
int hash_round(unsigned long code, int mod_value);
hash_table * create_hash_table();
void create_hash_node(hash_bucket * node);
trie_node * hash_insert(hash_table * table, char * word);
trie_node * hash_bucket_insert(hash_table * table, int pos, char * word);
int expand_hash_table(hash_table * table);
trie_node * hash_search(hash_table * table, char * word);
int hash_delete(hash_table * table, char * word);
void hash_clean(hash_table ** table);


#endif

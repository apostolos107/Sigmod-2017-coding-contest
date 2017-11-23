#ifndef __BLOOM_FILTER__
#define __BLOOM_FILTER__

#include "murmur3.h"
#include <string.h>

#define SIZE 100000
#define HASH 3

extern struct bloom_filter* bloom;


typedef struct bloom_filter{
    int size;
    int hash_amount;
    int* vector;
}bloom_filter;

bloom_filter* bloom_filter_init();
void bloom_filter_destroy(bloom_filter**);
int bloom_insert_and_check(char* ngram,bloom_filter* bloom);
int* hash_results(char*,bloom_filter*);
int bloom_check(char*,bloom_filter*);
void print_vector(bloom_filter*);
void clean_vector(bloom_filter*);

#endif

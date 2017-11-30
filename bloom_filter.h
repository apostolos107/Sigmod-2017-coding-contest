#ifndef __BLOOM_FILTER__
#define __BLOOM_FILTER__

#include <string.h>

#define SIZE 200000
#define HASH 3

#include <stdint.h>
#include <stddef.h>

extern struct bloom_filter* bloom;





typedef struct bloom_filter{
    int size;
    int hash_amount;
    char* vector;
}bloom_filter;

bloom_filter* bloom_filter_init();
void bloom_filter_destroy(bloom_filter**);
int bloom_insert_and_check(char* ngram,bloom_filter* bloom);
int* hash_results(char*,bloom_filter*);
int bloom_check(char*,bloom_filter*);
void print_vector(bloom_filter*);
void clean_vector(bloom_filter*);

unsigned long murmur3(const uint8_t* key, size_t len, unsigned long seed);

#endif

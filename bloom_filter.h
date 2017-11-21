#ifndef __BLOOM_FILTER__
#define __BLOOM_FILTER__

#include "murmur3.h"

typedef struct bloom_filter{
    int size;
    int hash_amount;
    int* vector;
}bloom_filter;

bloom_filter* bloom_filter_init(int,int);
void bloom_filter_destroy(bloom_filter**);
int* hash_results(char*,bloom_filter*);
int bloom_check(char*,bloom_filter*);


#endif

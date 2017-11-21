#include <stdio.h>
#include <stdlib.h>

#include "bloom_filter.h"
#include "murmur3.h"

bloom_filter* bloom_filter_init(int size,int hash_amount)
{
    bloom_filter* new_bloom=malloc(sizeof(bloom_filter));
    new_bloom->vector=malloc(size*sizeof(int));
    new_bloom->hash_amount=hash_amount;
    new_bloom->size=size;
    return  new_bloom ;
}

void bloom_filter_destroy(bloom_filter** bloom)
{
    free((*bloom)->vector);
    free(bloom);
}


void bloom_insert(char* ngram,bloom_filter* bloom)
{
    int i;
    int* result = hash_results(ngram,bloom);
    for(i = 0 ; i < bloom->hash_amount ; i++)
    {
        bloom->vector[result[i]]=1;
    }
    free(result);
}

int bloom_check(char* ngram,bloom_filter* bloom)
{
    int i;
    int* result = hash_results(ngram,bloom);
    for(i = 0 ; i < bloom->hash_amount ; i++)
    {
        if(bloom->vector[result[i]]==0)
        {
            free(result);
            return 0;
        }
    }
    free(result);
    return 1;
}

int* hash_results(char* value, bloom_filter* bloom) {
        int* result = malloc(sizeof(int)*bloom->hash_amount);
        long hash1 = murmur3(0, value);
        long hash2 = murmur3((int) hash1, value);
        for (int i = 0; i < bloom->hash_amount; i++) {
            result[i] = (int) ((hash1 + i * hash2) % bloom->size);
        }
        return result;
}

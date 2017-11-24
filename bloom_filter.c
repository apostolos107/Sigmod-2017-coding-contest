#include <stdio.h>
#include <stdlib.h>

#include "bloom_filter.h"
#include "murmur3.h"

unsigned long my_word(char * str)
{
    unsigned long hash = 0;
    int c;

    while (c = *str++)
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}


bloom_filter* bloom_filter_init()
{
    bloom_filter* new_bloom=malloc(sizeof(bloom_filter));
    new_bloom->vector=calloc(SIZE,sizeof(char));
    new_bloom->hash_amount=HASH;
    new_bloom->size=SIZE;
    return  new_bloom ;
}

void bloom_filter_destroy(bloom_filter** bloom)
{
    free((*bloom)->vector);
    free(*bloom);
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


int bloom_insert_and_check(char* ngram,bloom_filter* bloom)
{
    int i;
    int flag = 1;
    int* result = hash_results(ngram,bloom);
    for(i = 0 ; i < bloom->hash_amount ; i++)
    {
        if(bloom->vector[result[i]]==0)
        {
            bloom->vector[result[i]]=1;
            flag = 0;
        }
    }
    free(result);
    return flag;
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
        int bad_hash = my_word(value) % bloom->size;
        unsigned long hash1 = murmur3(value, strlen(value), 0);
        unsigned long hash2 = murmur3(value, strlen(value),hash1);
        for (int i = 0; i < bloom->hash_amount; i++) {
            result[i] = ( ( hash1 + i * hash2) % bloom->size);
            // printf("%d\n",result[i] );
        }
        return result;
}

void clean_vector(bloom_filter* bloom){
    memset(bloom->vector, 0, bloom->size*sizeof(char));
    // int i;
    // for(i =0 ; i<bloom->size ; i++)bloom->vector[i]=0;
}

void print_vector(bloom_filter* bloom){
    int i;
    for(i=0 ; i<bloom->size;i++){
        printf("%d", bloom->vector[i]);
    }
    printf("\n" );
}

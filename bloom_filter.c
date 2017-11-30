#include <stdio.h>
#include <stdlib.h>

#include "bloom_filter.h"
#include "murmur3.h"

unsigned long my_word(char * str)
{   /* hash function that converts string to long value */
    unsigned long hash = 0;
    int c;

    while (c = *str++)
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}


bloom_filter* bloom_filter_init()
{   /* Malloc the required memory for the bloom filter */
    bloom_filter* new_bloom=malloc(sizeof(bloom_filter));
    new_bloom->vector=calloc(SIZE,sizeof(char));
    new_bloom->hash_amount=HASH;
    new_bloom->size=SIZE;
    return  new_bloom ;
}

void bloom_filter_destroy(bloom_filter** bloom)
{   /* Free the memory that was allocated for the bloom filter */
    free((*bloom)->vector);
    free(*bloom);
}

int bloom_insert_and_check(char* ngram,bloom_filter* bloom)
{   /* get an n-gram check if it is already in the result_of_search
    and if it isn't, just add it. Return yes or no */
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

int* hash_results(char* value, bloom_filter* bloom) {
        /* use murmur with different seeds to get the hash values
        and then use Cassandra to get the positions to the vector */

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
    /* Set all the vector to 0 */
    memset(bloom->vector, 0, bloom->size*sizeof(char));
}

void print_vector(bloom_filter* bloom){
    /* used for testing */
    int i;
    for(i=0 ; i<bloom->size;i++){
        printf("%d", bloom->vector[i]);
    }
    printf("\n" );
}

unsigned long murmur3(const uint8_t* key, size_t len, unsigned long seed) {
    unsigned long h = seed;
    if (len > 3)
    {
        const int* key_x4 = (const int*) key;
        size_t i = len >> 2;
        do {
            unsigned long k = *key_x4++;
            k *= 0xcc9e2d51;
            k = (k << 15) | (k >> 17);
            k *= 0x1b873593;
            h ^= k;
            h = (h << 13) | (h >> 19);
            h = (h * 5) + 0xe6546b64;
        } while (--i);
        key = (const uint8_t*) key_x4;
    }
    if (len & 3)
    {
        size_t i = len & 3;
        unsigned long k = 0;
        key = &key[i - 1];
        do {
            k <<= 8;
            k |= *key--;
        } while (--i);
        k *= 0xcc9e2d51;
        k = (k << 15) | (k >> 17);
        k *= 0x1b873593;
        h ^= k;
    }
    h ^= len;
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    return h;
}

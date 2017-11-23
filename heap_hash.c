#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heap_hash.h"
#include "tools.h"

/*   sdbm hash function from:
    http://www.cse.yorku.ca/~oz/hash.html */
unsigned long heap_hash_word(char * str)
{
    unsigned long hash = 0;
    int c;

    while (c = *str++)
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}

int heap_hash_round(unsigned long code, int mod_value)
{
    return (int) (code%mod_value);
}

heap_hash_table * heap_create_hash_table()
{
    heap_hash_table * table = malloc(sizeof(heap_hash_table));

    table->max_breaking = HASH_START_SIZE;
    table->current_breaking = 0;
    table->round = 0;
    table->size = HASH_START_SIZE;
    table->mod_value =HASH_START_SIZE;
    table->buckets = malloc(HASH_START_SIZE *sizeof(heap_hash_bucket));
    int i;
    for(i=0; i<HASH_START_SIZE; i++){
        heap_create_hash_node(&table->buckets[i]);
    }
    return table;
}

void heap_create_hash_node(heap_hash_bucket * node)
{
    node->current_children =0;
    node->max_children = BUCKET_START_SIZE;

    node->children = NULL;
}

heap_node * heap_hash_insert(heap_hash_table * table, char * word)
{
    unsigned long code = heap_hash_word(word);
    int position = heap_hash_round(code, table->mod_value);
    if (position < table->current_breaking)
    {
        position = heap_hash_round(code, table->mod_value *2);
    }
    return heap_hash_bucket_insert(table, position, word);
}

heap_node * heap_hash_bucket_insert(heap_hash_table * table, int pos, char * word)
{
    heap_hash_bucket * current_bucket = &table->buckets[pos];
    if(current_bucket->children == NULL)
    {
        current_bucket->current_children++;
        current_bucket->children = malloc(BUCKET_START_SIZE*sizeof(heap_hash_table*));
        current_bucket->children[0] = create_node();
        table->buckets[pos].children[0]->content = copy_string(word);

        return current_bucket->children[0];
    }
    else if(current_bucket->current_children == current_bucket->max_children)
    {/*SFAGI*/
        heap_expand_hash_table(table);
        unsigned long code = heap_hash_word(word);
        pos = heap_hash_round(code, table->mod_value);
        if (pos < table->current_breaking)
        {
            pos = heap_hash_round(code, table->mod_value *2);
        }
        if(table->buckets[pos].current_children == table->buckets[pos].max_children)
        {
            table->buckets[pos].max_children += BUCKET_START_SIZE;
            table->buckets[pos].children = realloc(table->buckets[pos].children,  table->buckets[pos].max_children*sizeof(trie_node));
        }
        current_bucket = & table->buckets[pos];
    }

    int spot_on_bucket;
    int found = heap_binary_search_array(current_bucket->children, current_bucket->current_children, word, &spot_on_bucket);
    if(found == -1)
    {
        memmove(&current_bucket->children[spot_on_bucket+1], &current_bucket->children[spot_on_bucket], (current_bucket->current_children-spot_on_bucket)*sizeof(heap_node*));
        current_bucket->children[spot_on_bucket] =create_node();
        current_bucket->children[spot_on_bucket]->content = copy_string(word);
        current_bucket->current_children ++;
    }
    return current_bucket->children[spot_on_bucket];
}

int heap_expand_hash_table(heap_hash_table * table)
{
    table->size++;
    table->buckets = realloc(table->buckets, table->size * sizeof(hash_bucket));
    heap_create_hash_node(&table->buckets[table->size-1]);

    heap_hash_bucket * breaking_bucket = &table->buckets[table->current_breaking];
    heap_hash_bucket * new_bucket = &table->buckets[table->size-1];
    int move_left = 0;
    for (int i = 0; i < breaking_bucket->current_children; i++)
    {
        int new_pos = heap_hash_round(heap_hash_word(breaking_bucket->children[i]->content), table->mod_value*2);
        if(new_pos == table->current_breaking)
        {
            if(move_left!=0){
                //must move it
                //also at the end
                memmove(&breaking_bucket->children[i-move_left], &breaking_bucket->children[i], (breaking_bucket->current_children-i)*sizeof(heap_node*));
                i-=move_left;
                breaking_bucket->current_children-=move_left;
                move_left=0;
            }
        }
        else
        {
            if(new_bucket->children==NULL)
            {   /* first trie node in the bucket */
                new_bucket->children=malloc(sizeof(trie_node)*BUCKET_START_SIZE);
            }

            if(new_bucket->current_children == new_bucket->max_children)
            {   /* we need to resize our new_bucket cause we have more elements */
                new_bucket->max_children+=BUCKET_START_SIZE;
                new_bucket->children=realloc(new_bucket->children, sizeof(trie_node)*new_bucket->max_children);
            }
            memcpy(&new_bucket->children[new_bucket->current_children],&breaking_bucket->children[i],sizeof(trie_node));

            new_bucket->current_children++;
            move_left++;
        }
    }
    if(move_left!=0){
        /* the final move left children are not there anymore */
        breaking_bucket->current_children-=move_left;
        move_left=0;
    }
    /* increase the pointer to the next bucket */
    table->current_breaking++;
    if(table->current_breaking==table->max_breaking)
    {   /* reset the round */
        table->current_breaking=0;
        table->max_breaking*=2;
        table->round++;
        table->mod_value*=2;
    }
}

heap_node * heap_hash_search(heap_hash_table * table, char * word)
{
    unsigned long word_hash = heap_hash_word(word);
    int bucket_pos = heap_hash_round(word_hash,table->mod_value);
    if(bucket_pos < table->current_breaking){
        //if it belongs to one of the buckets that has been split
        bucket_pos = heap_hash_round(word_hash, table->mod_value*2);
    }
    //the bucket that it supose to be
    heap_hash_bucket* cur_bucket = &table->buckets[bucket_pos];
    int pos,found;

    //do binary search in the array
    found = heap_binary_search_array(cur_bucket->children, cur_bucket->current_children, word, &pos);
    if(found==1){
        //if found return the trie_node
        return cur_bucket->children[pos];
    }else{
        return NULL;
    }

}

int heap_hash_delete(heap_hash_table * table, char * word)
{
    unsigned long code = heap_hash_word(word);
    int position = heap_hash_round(code, table->mod_value);
    if (position < table->current_breaking)
    {
        position = heap_hash_round(code, table->mod_value *2);
    }

    return heap_hash_bucket_delete(&table->buckets[position], word);
}

int heap_hash_bucket_delete(heap_hash_bucket * bucket, char * word)
{
    int i;
    int spot, found;
    found = heap_binary_search_array(bucket->children, bucket->current_children, word, &spot);
    if(found==1)
    {
        free(bucket->children[spot]->content);
        // free(bucket->children[spot].children);
        if( (bucket->current_children-1)!=spot && (bucket->current_children-1)>0 ){
            memmove(&bucket->children[spot],&bucket->children[spot+1],(bucket->current_children-spot-1)*sizeof(heap_node*));
        }
        bucket->current_children--;
        return 1;
    }
    return -1;
}

void heap_hash_clean(heap_hash_table ** table)
{
    heap_hash_table* my_table = *table;
    int i;
    for (i = 0; i < my_table->size; i++) {
        //for each bucket in the table
        heap_hash_bucket* cur_bucket = &my_table->buckets[i];
        int j;
        for ( j = 0; j < cur_bucket->current_children; j++) {
            free(cur_bucket->children[j]->content);
            free(cur_bucket->children[j]);
        }
        free(cur_bucket->children);
    }

    free(my_table->buckets);
    free(*table);
}
int heap_binary_search_array(heap_node** array, int size, char* word, int* spot_ptr_arg){
    int spot = 0;//the current spot
    int a = 0;//the base index in array
    int b = size;//the max index in array
    int found_word = 0;//bool, 1 if found
    int m;//the middle of hte [a,b]
    if(size==0){
        //if no childrens
        if(spot_ptr_arg!=NULL){
            *spot_ptr_arg=0;
        }
        return -1;
    }
    while((a <= b) && (a< size))
    {
        m = (a + b) /2;
        if ( strcmp(word, array[m]->content) == 0)
        { /*this sentence exist as far as here*/
            spot = m;
            found_word =1;
            break;
        }
        else if( strcmp(word, array[m]->content) < 0)
        {/*word belongs before this child*/
            b = m-1;
            spot = m;
        }
        else if( strcmp(word, array[m]->content) > 0)
        {/*word belongs after this child*/
            a = m+1;
            spot = a;
        }
        // printf("A is %d , B is %d\n",a,b );

    }
    if(spot_ptr_arg!=NULL){
        *spot_ptr_arg=spot;
    }
    if(found_word==0){
        return -1;
    }else{
        return 1;
    }
}

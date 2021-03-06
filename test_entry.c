#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "trie.h"
#include "heap.h"
#include "heap.h"
#include "hash_table.h"

bloom_filter * bloom ;

void test_insert_trie(char * sentence)
{
    trie * mytree;
    mytree = init_trie();
    heap* my_heap = heap_create();

    int result = insert_ngram(mytree, sentence);
    assert(result == 1);

    if(!(sentence == NULL || strcmp(sentence, "")==0)){
        assert(hash_search(mytree->children,"hey")!=NULL);
    }

    assert(trie_clean(&mytree) == 1);
}

//init a trie with some ngrams
trie* init_test_trie(){
    trie * mytree = malloc(sizeof(trie));
    heap* top = heap_create();
    mytree = init_trie();

    // check the capitals
    char sentence1[]="IS A RED CAR";
    int result = insert_ngram(mytree,sentence1);
    assert(result == 1);

    char sentence2[]="is a red car";
    result = insert_ngram(mytree,sentence2);
    assert(result == 1);

    char sentence3[]="Is a Red Car";
    result = insert_ngram(mytree,sentence3);
    assert(result == 1);

    char search1[]="Is a Red Car";
    result_of_search* search_result=search(mytree,search1,top);
    assert(search_result->num_of_results==1);
    delete_result(&search_result);

    char search2[]="iS A rEd car";
    search_result=search(mytree,search2,top);
    assert(search_result->num_of_results==0);
    delete_result(&search_result);

    heap_destroy(&top);
    return mytree;
}

// check the children tables when reallocing (the children table of is needs one more)
void test_realloc(trie* mytree){
    int i,result;
    char* sentence;
    char* temp;
    result_of_search* search_result;
    heap* top = heap_create();

    sentence=malloc(sizeof(char)*(NUMBER_OF_CHILDREN+5));
    strcpy(sentence,"is ");
    for( i = 0 ; i <= NUMBER_OF_CHILDREN ; i++ )
    {
        strcat(sentence,"a");
        temp=malloc(sizeof(char)*(strlen(sentence)+1));
        strcpy(temp,sentence);
        result = insert_ngram(mytree,temp);
        free(temp);
        assert(result == 1);
    }
    search_result=search(mytree,sentence,top);
    assert(search_result->num_of_results==1);
    delete_result(&search_result);
    free(sentence);

    heap_destroy(&top);

}

//check the delete
void test_delete(trie* mytree){
    int result;
    result_of_search* search_result;
    heap* top = heap_create();

    if(NUMBER_OF_CHILDREN==0){
        printf("The number of children is 0\n");
        assert(NUMBER_OF_CHILDREN>0);
    }

    //add the "is" ngram
    char sentence0[]="is";
    result = insert_ngram(mytree,sentence0);
    assert(result == 1);

    //check the delete
    char delete_sentence0[]="is a";
    delete_ngram(mytree,delete_sentence0);
    search_result=search(mytree,delete_sentence0,top);
    //the results must be 1 because of the "is" ngram and because we deleted "is a"
    // else it is should be 0 or 2 if the delete is not correct
    assert(search_result->num_of_results==1);
    delete_result(&search_result);
    heap_destroy(&top);
}

void test_insert_search_delete()
{

    trie* mytree=init_test_trie();
    test_realloc(mytree);
    test_delete(mytree);
    assert(trie_clean(&mytree)==1);
    assert(mytree==NULL);
}


void test_insert_cases()
{
    char sentence1[]= "hey buddy";
    test_insert_trie(sentence1);
    char sentence2[]="";
    test_insert_trie(sentence2);
    char sentence3[]= "  hey  buddies  ";
    test_insert_trie(sentence3);
}

void test_heap_inserts(){
    heap* my_heap = NULL;
    my_heap = heap_create();
    char a_word[1024];
    for (size_t i = 0; i < 1000; i++) {
        a_word[i]='a'+i%24;
        a_word[i+1]='\0';
        heap_insert(my_heap, a_word);
    }
    heap_insert(my_heap, "good thing");
    heap_insert(my_heap, "good thing");
    heap_insert(my_heap, "good thing");
    heap_insert(my_heap, "good");
    heap_insert(my_heap, "good");
    heap_insert(my_heap, "good");
    heap_insert(my_heap, "good");
    heap_insert(my_heap, "dog");
    heap_insert(my_heap, "dog");
    heap_insert(my_heap, "cat");
    heap_insert(my_heap, "cat");
    heap_insert(my_heap, "wow");
    heap_insert(my_heap, "wow");
    heap_insert(my_heap, "wow");
    heap_insert(my_heap, "wow");
    heap_insert(my_heap, "wow");

    assert(strcmp(my_heap->root->content,"wow")==0);

    heap_destroy(&my_heap);

}

void test_heap_cmp(){
    heap_node heap_1,heap_2;
    heap_1.content=copy_string("a");
    heap_1.appeared=0;

    heap_2.content=copy_string("b");
    heap_2.appeared=0;

    assert(cmp_heap_node(&heap_1, &heap_2)>0);

}

void is_ok(heap_node* cur_node, int depth){
    if(cur_node==NULL){
        return ;
    }
    heap_node *left = cur_node->left;
    heap_node *right = cur_node->right;
    if(left!=NULL){
        assert(cmp_heap_node(left, cur_node)<0);
        is_ok(left,depth+1);
    }
    if(right!=NULL){
        assert(cmp_heap_node(right, cur_node)<0);
        is_ok(right,depth+1);
    }
}

int test_heap_util(){
    heap* my_heap = heap_create();
    heap_insert(my_heap, "good thing");
    heap_insert(my_heap, "good thing");
    heap_insert(my_heap, "good thing");
    heap_insert(my_heap, "good");
    heap_insert(my_heap, "good");
    heap_insert(my_heap, "good");
    heap_insert(my_heap, "good");
    heap_insert(my_heap, "dog");
    heap_insert(my_heap, "dog");
    heap_insert(my_heap, "cat");
    heap_insert(my_heap, "cat");
    heap_insert(my_heap, "wow");
    heap_insert(my_heap, "wow");
    heap_insert(my_heap, "wow");
    heap_insert(my_heap, "wow");
    heap_insert(my_heap, "wow");

    is_ok(my_heap->root,0);
}

void test_heap(){
    test_heap_cmp();
    test_heap_inserts();
    assert(test_heap_util()==0);
}

int main(void)
{
    bloom=bloom_filter_init();
    test_insert_cases();
    test_insert_search_delete();
    test_heap();
    bloom_filter_destroy(&bloom);
    printf("Passed the test!\n");
    return 0;
}

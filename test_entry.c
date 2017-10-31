#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "trie.h"


void test_insert_trie(char * sentence)
{
    trie * mytree = malloc(sizeof(trie));
    mytree->root = init_trie();

    int result = insert_ngram(mytree, sentence);
    assert(result == 1);

    if(!(sentence == NULL || strcmp(sentence, "")==0))
        assert(strcmp(mytree->root->children[0].word, "hey")==0);

    assert(trie_clean(&mytree) == 1);
}

//init a trie with some ngrams
trie* init_test_trie(){
    trie * mytree = malloc(sizeof(trie));
    mytree->root = init_trie();

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
    result_of_search* search_result=search(mytree,search1);
    assert(search_result->num_of_results==1);
    delete_result(&search_result);

    char search2[]="iS A rEd car";
    search_result=search(mytree,search2);
    assert(search_result->num_of_results==0);
    delete_result(&search_result);
    return mytree;
}

// check the children tables when reallocing (the children table of is needs one more)
void test_realloc(trie* mytree){
    int i,result;
    char* sentence;
    char* temp;
    result_of_search* search_result;
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
    search_result=search(mytree,sentence);
    assert(search_result->num_of_results==1);
    delete_result(&search_result);
    free(sentence);
}

//check the delete
void test_delete(trie* mytree){
    int result;
    result_of_search* search_result;
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
    search_result=search(mytree,delete_sentence0);
    //the results must be 1 because of the "is" ngram and because we deleted "is a"
    // else it is should be 0 or 2 if the delete is not correct
    assert(search_result->num_of_results==1);
    delete_result(&search_result);
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

 int main(void)
 {
    test_insert_cases();
    test_insert_search_delete();
    printf("Passed the test!\n");
    return 0;
}

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

void test_insert_search_delete()
{
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

    // check the children tables when reallocing (the children table of is needs one more)
    int i;
    char* sentence;
    char* temp;
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

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

    assert(trie_clean(mytree) == 1);
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
    printf("Passed the test!\n");
    return 0;
}

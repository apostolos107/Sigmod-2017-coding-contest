#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"
#include "tools.h"

trie_node * init_trie()
{
    trie_node * node = create_trie_node();

    if(node == NULL)
        error_exit("Malloc Failure");

    node->word = malloc(1*sizeof(char));
    node->word[0] = '\0';

    return node;
}


OK_SUCCESS insert_ngram(trie * my_trie, char * ngram)
{
    return insert_ngram_to_node(my_trie->root, ngram);
}

OK_SUCCESS delete_ngram(trie * my_trie, char * ngram)
{
    trie_node* root=my_trie->root;
    char* word=strtok(ngram," ");
    if(word==NULL)return -1;
    return anadromic_delete(root,word);
}

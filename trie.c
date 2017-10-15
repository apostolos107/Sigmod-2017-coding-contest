#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"
#include "tools.h"

typedef struct result_of_search{
    char* cur_word;
    int current_size;
    int num_of_results;
} result_of_search;

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

char* search(trie* my_trie,char* the_ngram)
{
    char* current_sub_str=&the_ngram[0];//start from the begining
    result_of_search* result = malloc(sizeof(result_of_search));
    result->cur_word=NULL;
    result->current_size=0;
    result->num_of_results=0;

    result->current_size=1024;
    result->cur_word=malloc(sizeof(char)*result->current_size);
    while(current_sub_str[0]!='\0'){
    //while you don't have just a space or just a \0

/***********************search for this ngram*************/
        printf("Search for{%s}\n",current_sub_str);
        char* search_for=copy_string(current_sub_str);
        trie_node* cur_node = my_trie->root;
        char* thread_safe=NULL;//for strtok_r
        char* current_word;//the current word form iteration
        current_word=strtok_r(search_for," ",&thread_safe);
        //while we have nodes and the word is not finished
        while( current_word!=NULL){
            printf("\t%s\n",current_word);
            // int spot=search_kid(cur_node,);
            current_word=strtok_r(NULL," ",&thread_safe);
        }
/*****************end of search***************************/
        free(search_for);
        printf("End of search for %s\n",current_sub_str);
/******************get the next word**********************/
        while(current_sub_str[0]!='\0' && current_sub_str[0]!=' '){
            //search until the next space or the end of the word
            current_sub_str++;
        }
        if(current_sub_str[0]==' '){
            //if we found a space
            while(current_sub_str[0]==' '){
                current_sub_str++;//eat all white spaces
            }
        }
    }
    return result->cur_word;
}

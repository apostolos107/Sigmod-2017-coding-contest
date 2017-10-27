#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"
#include "tools.h"
#include "trie_node.h"

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

OK_SUCCESS trie_clean(trie* mytree){
    trie_node_clean(mytree->root);
    free(mytree->root);
    free(mytree);
    return 1;
}

OK_SUCCESS delete_ngram(trie * my_trie, char * ngram)
{
    return trie_delete(my_trie->root,ngram);
}
//
// result_of_search* search(trie* my_trie,char* the_ngram)
// {
//     char* current_sub_str=&the_ngram[0];//start from the begining
//     result_of_search* result = new_result(1024);

result_of_search* search(trie* my_trie,char* the_ngram)
{
    char* current_sub_str=&the_ngram[0];//start from the begining
    result_of_search* result = new_result(1024);

    while(current_sub_str[0]!='\0'){
    //while you don't have just a space or just a \0

/***********************search for this ngram*************/
        int offset=0;//it's the offset of the current_sub_str to the word we are now
        // printf("Search for{%s}\n",current_sub_str);
        //i copy the srting because it changes with strtok
        char* search_for=copy_string(current_sub_str);
        trie_node* cur_node = my_trie->root;//start from the root
        char* thread_safe=NULL;//for strtok_r
        char* current_word;//the current word form iteration
        current_word=strtok_r(search_for," ",&thread_safe);//get the first word
        offset+=strlen(current_word);
        //while we have nodes and the word is not finished
        while(cur_node->word!=NULL && current_word!=NULL){
            int spot_of_word,return_value;
            printf("\t{%s} ",current_word);fflush(stdout);
            // int spot=search_kid(cur_node,);
            return_value=binary_search_kid(cur_node, current_word, &spot_of_word);
            if (return_value==1) {
                printf("\tFOUND at %d ",spot_of_word);fflush(stdout);
                if(cur_node->children[spot_of_word].is_final=='Y'){
                    printf("\t and it's final|SO I ADD TO RESULT|\n");
                    char old = current_sub_str[offset];
                    current_sub_str[offset]='\0';
                    printf("I add[%s]\n",current_sub_str);
                    add_to_result(result,current_sub_str);
                    current_sub_str[offset]=old;
                }
                cur_node=&cur_node->children[spot_of_word];//go deeper
            } else {
                printf("\tNOT FOUND at %d\n",spot_of_word);
                cur_node=NULL;
                break;
            }

            current_word=strtok_r(NULL," ",&thread_safe);//go to next word
            if(current_word!=NULL){
                offset+=strlen(current_word)+1;//for the space
            }
            //go deeper
            printf("\n---\n" );
        }
/*****************end of search***************************/
        free(search_for);
        // printf("End of search for %s\n",current_sub_str);
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
    return result;
}

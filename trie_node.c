#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"
#include "tools.h"

trie_node* create_trie_node()
{
    trie_node * node = malloc(sizeof(trie_node));

    if(node == NULL)
        error_exit("Malloc Failure");

    node->is_final = 'N';
    node->current_children = 0;
    node->max_children = NUMBER_OF_CHILDREN;
    node->word=NULL;
    node->children = malloc(node->max_children * sizeof(trie_node));
    return node;
}

void init_trie_node(trie_node * node)
{
    if(node == NULL)
        error_exit("Malloc Failure");

    node->is_final = 'N';
    node->current_children = 0;
    node->max_children = NUMBER_OF_CHILDREN;
    node->word=NULL;
    node->children = malloc(node->max_children * sizeof(trie_node));
}

OK_SUCCESS insert_ngram_to_node(trie_node * node, char * ngram)
{
    trie_node * temp = node;
    char * word = strtok(ngram, " ");

    int a , b , m, found_word;
    int spot=0;

    while(1)
    {
        if(temp->current_children == 0 )
        { /*we need to add a new child cause this node has 0 of them */
            init_trie_node(&temp->children[0]);
            temp->children[0].word = copy_string(word);
            spot = 0;
            temp->current_children ++;
            printf("prosthetw tin leksi %s afou exei 0 paidia\n", word);

        }
        else
        {
            found_word = binary_search_kid(temp, word, &spot);
            if( found_word==-1)
            {/*add a new child at the {spot} position*/
                // printf("Spot is %d\n", spot );
                if(temp->current_children == temp->max_children)
                {/*we need to give more space to our children's array*/
                    temp->max_children *=2;
                    temp->children = realloc(temp->children, temp->max_children*sizeof(trie_node));
                }
                int i;
                /*move the elements so we can make space for the new child*/
                // for (i = temp->current_children-1; i >= spot; i--)
                memmove(&temp->children[spot+1], &temp->children[spot], (temp->current_children-spot)*sizeof(trie_node));
                // temp->children[i+1] = temp->children[i];
                /*create the new child*/
                init_trie_node(&temp->children[spot]);
                temp->children[spot].word = copy_string(word);
                temp->current_children ++;

                printf("prosthetw tin leksi %s \n", word);
            }

        }

        word = strtok(NULL, " ");
        if (word == NULL)
        {/*end of N-Gram*/
            temp->children[spot].is_final = 'Y';
            return 1;
        }
        /*next word of our N-Gram*/
        temp = &temp->children[spot];
    }
}
//
OK_SUCCESS delete_node_child(trie_node* node,int position)
{   /* free the child */
    free(node->children[position].children);
    free(node->children[position].word);

    /*fill the gap in the children array that created due to the removal*/
    /*delete the last child because it is dublicate*/
    if(node->current_children-1!=position && (node->current_children-1)>0){
        memmove(&node->children[position], &node->children[position+1], (node->current_children-position-1)*sizeof(trie_node));
    }
    node->current_children--;

    return 1;
}

OK_SUCCESS trie_delete(trie_node* node,char* ngram)
{
    int position,found,stack_count=0;
    int stack_size=count_words(ngram);
    stack_node* stack;
    stack=malloc(stack_size*sizeof(stack_node));
    trie_node* temp_trie_node;
    temp_trie_node=node;
    char* word=strtok(ngram," ");
    if(word==NULL){
        free(stack);
        return -1;
    }
    while(1)
    {
        if(word==NULL)
        {/*end of N-gram*/
            break;
        }
        found=binary_search_kid(temp_trie_node,word,&position);
        if(found==-1)
        {/*the requested N-Grams doesn't exist */
            printf("i leksi %s den iparxi\n", word);
            free(stack);
            return -1 ;
        }
        if(stack_count>=stack_size)
        {
            printf("There is overflow in stack\n" );
            free(stack);
            return -1;
        }
        stack[stack_count].node=temp_trie_node;
        stack[stack_count].position=position;
        stack_count++;
        temp_trie_node=&temp_trie_node->children[position];
        /*get next word of our N-Gram*/
        word=strtok(NULL, " ");
    }
    stack_count--;
    if(stack[stack_count].node->children[stack[stack_count].position].is_final=='Y')
    {/*It must be a final word*/
        stack[stack_count].node->children[stack[stack_count].position].is_final='N';
        if(stack[stack_count].node->children[stack[stack_count].position].current_children==0)
        {
            printf("Delete %s\n",stack[stack_count].node->children[stack[stack_count].position].word );
            delete_node_child(stack[stack_count].node,stack[stack_count].position);
        }
    }
    else
    {
        printf("It is not a Final\n");
        free(stack);
        return -1;
    }
    stack_count--;
    while(stack_count>=0){
        /*It is a middle word or the first*/
        printf("Trying to delete %s\n",stack[stack_count].node->children[stack[stack_count].position].word );
        if(stack[stack_count].node->children[stack[stack_count].position].current_children==0 && stack[stack_count].node->children[stack[stack_count].position].is_final!='Y')
        {
            /*If there are not children and It is not a final*/
            delete_node_child(stack[stack_count].node,stack[stack_count].position);
            printf("deleted\n" );
        }
        stack_count--;
    }
    free(stack);
    return 1;

}


//binary search that returns the index in the array of the children
int binary_search_kid(trie_node* master_node,char* word,int* spot_ptr_arg){
    int spot = 0;//the current spot
    int a = 0;//the base index in array
    int b = master_node->current_children;//the max index in array
    int found_word = 0;//bool, 1 if found
    int m;//the middle of hte [a,b]
    if(master_node->current_children==0){
        //if no childrens
        if(spot_ptr_arg!=NULL){
            *spot_ptr_arg=0;
        }
        return -1;
    }
    while((a <= b) && (a< master_node->current_children))
    {
        m = (a + b) /2;
        // printf("M is %d\n", m);
        if ( strcmp(word, master_node->children[m].word) == 0)
        { /*this sentence exist as far as here*/
            spot = m;
            found_word =1;
            // printf("i leksi %s ipirxe\n", word);
            break;
        }
        else if( strcmp(word, master_node->children[m].word) < 0)
        {/*word belongs before this child*/
            if(m == 0)
            {
                spot = 0;
                break;
            }
            b = m-1;
            spot = b;
        }
        else if( strcmp(word, master_node->children[m].word) > 0)
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

OK_SUCCESS trie_node_clean(trie_node* node){
    int i;
    for(i=0;i<node->current_children;i++){
        trie_node_clean(&node->children[i]);
    }
    free(node->word);
    free(node->children);
    return 1;
}

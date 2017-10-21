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
    node->parent = NULL;
    return node;
}

void init_trie_node(trie_node * node, trie_node* parent)
{
    if(node == NULL)
        error_exit("Malloc Failure");

    node->is_final = 'N';
    node->current_children = 0;
    node->max_children = NUMBER_OF_CHILDREN;
    node->word=NULL;
    node->parent = parent;
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
            init_trie_node(&temp->children[0], temp);
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
                    temp->children = realloc(temp->children, temp->max_children*sizeof(trie_node *));
                }

                int i;
                /*move the elements so we can make space for the new child*/
                // for (i = temp->current_children-1; i >= spot; i--)
                    memmove(&temp->children[spot+1], &temp->children[spot], (temp->current_children-spot)*sizeof(trie_node));
                    // temp->children[i+1] = temp->children[i];
                /*create the new child*/
                init_trie_node(&temp->children[spot], temp);
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
        printf("I am in \n" );
        memmove(&node->children[position], &node->children[position+1], (node->current_children-position-1)*sizeof(trie_node));
    }
    node->current_children--;

    return 1;
}

OK_SUCCESS trie_delete(trie_node* node,char* ngram)
{
    int position,found,depth_count=0;
    int stack_size=count_words(ngram);
    int* positions;
    positions=malloc(stack_size*sizeof(int));
    trie_node* temp_trie_node;
    trie_node* parent;
    temp_trie_node=node;
    char* word=strtok(ngram," ");
    if(word==NULL){
        // free(stack);
        return -1;
    }
    while(1)
    {
        if(word==NULL)
        {/*end of N-gram*/
            break;
        }
        if(depth_count>=stack_size){
            printf("Stack Overflow\n");
            free(positions);
            return -1;
        }
        found=binary_search_kid(temp_trie_node,word,&position);
        if(found==-1)
        {/*the requested N-Grams doesn't exist */
            printf("i leksi %s den iparxi\n", word);
            free(positions);
            return -1 ;
        }
        temp_trie_node=&temp_trie_node->children[position];
        positions[depth_count]=position;
        depth_count++;
        /*get next word of our N-Gram*/
        word=strtok(NULL, " ");
    }
    depth_count--;
    parent=temp_trie_node->parent;
    if(temp_trie_node->is_final=='Y')
    {/*It must be a final word*/
        temp_trie_node->is_final='N';
        if(temp_trie_node->current_children==0)
        {
            printf("Delete %s\n",temp_trie_node->word );
            delete_node_child(parent,positions[depth_count]);
        }
    }
    else
    {
        printf("It is not a Final\n");
        free(positions);
        return -1;
    }
    depth_count--;
    while(depth_count>=0){
        temp_trie_node=parent;
        parent=temp_trie_node->parent;
        /*It is a middle word or the first*/
        printf("Trying to delete %s\n",temp_trie_node->word );
        if(temp_trie_node->current_children==0 && temp_trie_node->is_final!='Y')
        {
            /*If there are not children and It is not a final*/
            delete_node_child(parent,positions[depth_count]);
            printf("Deleted\n");
        }else{
            break;
        }
        depth_count--;
    }
    free(positions);
    return 1;

}
//


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

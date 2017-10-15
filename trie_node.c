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
    node->children = malloc(node->max_children * sizeof(trie_node *));

    return node;
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
            temp->children[0] = create_trie_node();
            temp->children[0]->word = copy_string(word);
            temp->current_children ++;
            printf("prosthetw tin leksi %s afou exei 0 paidia\n", word);

        }
        else
        {
            spot = 0;
            a = 0;
            b = temp->current_children;
            found_word = 0;


            while((a <= b) && (a< temp->current_children))
            {
                m = (a + b) /2;
                // printf("M is %d\n", m);
                if ( strcmp(word, temp->children[m]->word) == 0)
                { /*this sentence exist as far as here*/
                    spot = m;
                    found_word =1;
                    printf("i leksi %s ipirxe\n", word);
                    break;
                }
                else if( strcmp(word, temp->children[m]->word) < 0)
                {/*word belongs before this child*/
                    if(m == 0)
                    {
                        spot = 0;
                        break;
                    }
                    b = m-1;
                    spot = b;
                }
                else if( strcmp(word, temp->children[m]->word) > 0)
                {/*word belongs after this child*/
                    a = m+1;
                    spot = a;
                }
                // printf("A is %d , B is %d\n",a,b );

            }

            if( !found_word)
            {/*add a new child at the {spot} position*/
                // printf("Spot is %d\n", spot );
                if(temp->current_children == temp->max_children)
                {/*we need to give more space to our children's array*/
                    temp->max_children *=2;
                    temp->children = realloc(temp->children, temp->max_children*sizeof(trie_node *));
                }

                int i;
                /*move the elements so we can make space for the new child*/
                for (i = temp->current_children-1; i >= spot; i--)
                    temp->children[i+1] = temp->children[i];
                /*create the new child*/
                temp->children[spot] = create_trie_node();
                temp->children[spot]->word = copy_string(word);
                temp->current_children ++;

                printf("prosthetw tin leksi %s \n", word);
            }

        }

        word = strtok(NULL, " ");
        if (word == NULL)
        {/*end of N-Gram*/
            temp->is_final = 'Y';
            return 1;
        }
        /*next word of our N-Gram*/
        temp = temp->children[spot];
    }
}

OK_SUCCESS anadromic_delete(trie_node* node,char* remaining)
{
    if(remaining==NULL)
    {
        return 2;
    }
    char* newremaining=strtok(NULL, " ");
    int return_value=anadromic_delete(node,newremaining);
    if(return_value==1)
    {
        printf("%s\n",remaining);
        return 1;
    }else if(return_value==2){
        printf("I am the last: %s\n", remaining);
        return 1;
    }else{
        return -1;
    }
}

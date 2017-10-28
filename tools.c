#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"

int count_words(char * s)
{ /*count number of words so we can know the N of our N-Gram*/
  int found_letter = 0;
  int i;
  int count =0;

  for (i = 0;i<strlen(s);i++)
  {
   if (s[i] == ' ')
       found_letter = 0;
   else
   {
       if (found_letter == 0)
           count++;
       found_letter = 1;
   }
  }
  return count;
}

char * copy_string(char * s)
{
  char * new = malloc((strlen(s)+1)*sizeof(char));
  if(new == NULL)
    error_exit("Malloc Failure");
  strcpy(new, s);

  return new;
}

void error_exit(char * s)
{
  fprintf(stderr, "%s\n Program will stop! \n", s);
  exit(EXIT_FAILURE);
}


result_of_search* new_result(int size){
    result_of_search* result=malloc(sizeof(result_of_search));
    result->cur_word=malloc(sizeof(char)*size);
    result->current_size=size;
    result->current_wrote=0;
    result->num_of_results=0;

    result->cur_word[0]='\0';
    return result;
}

void delete_result(result_of_search** result){
    // free((*result)->cur_word);//do not delete the word, we need it
    free((*result)->cur_word);
    free(*result);
    *result=NULL;
}

int word_exists(result_of_search *result, char* first_word, char* last_word){
    char* temp;
    //find the first word
    // printf("\t===searching for {%s}...{%s} in {%s}\n",first_word,last_word,result->cur_word );
    temp=strstr(result->cur_word, first_word);
    while(temp!=NULL){
        // printf("===found strstr\n");
        int found = 1;
        char* current_word=first_word;
        while(current_word<=last_word){
            printf("temp->%s \t cur_wo->%s\n",temp,current_word);
            int word_size = strlen(current_word);
            if( strncmp(current_word,temp , word_size)==0 ){
                //if the word is ok
                if(temp[word_size]!=' ' && temp[word_size]!='|' && temp[word_size]!='\0'){
                    //it must be space or pipe
                    found=0;
                    while(*temp!='\0' && *temp!='|'){
                        temp++;
                    }
                    break;
                }else{

                }
                current_word+=word_size+1;//go to the next word to add_to_result
                temp+=word_size+1;//go to the next word in the already result
            }else{
                //the word is not ok
                found=0;
                break;
            }
        }
        if(found==1){
            //that means that all words matches ok
            //check if the next char is |
            // printf("===it's at the end{%s}\n", temp );
            if(temp[-1]=='|' || temp[-1]=='\0'){
                return 1;
            }
        }
        temp=strstr(temp, first_word);//find if there is next
    }
        //check the next one
            //if all exists and next symbol is |
    return 0;
}

void add_to_result(result_of_search* result,char* the_word,char* first_word){
    result->num_of_results++;
    int bytes_wrote;
    // printf("{%s}->{%s}\t{%s}[%d]\n",first_word,the_word,result->cur_word,result->current_wrote);
    int exists = word_exists(result,first_word,the_word);
    if(exists==1){
        // printf("Exists {%s}->{%s}\t{%s}[%d]\n",first_word,the_word,result->cur_word,result->current_wrote);
        // printf("\t===yes\n" );
        return;
    }else{
        // printf("\t===no\n" );
    }
    while(first_word<=the_word){
        // printf("$$$%s\n",first_word);
        int size_of_word = strlen(first_word);
        while( size_of_word + 2 + result->current_wrote > result->current_size){
            printf("we need to realloc %d->%d(+%d)\n",result->current_size,2*result->current_size,size_of_word );
            //we need to make it bigger
            result->current_size*=2;
            result->cur_word=realloc(result->cur_word, result->current_size);
            if(result->cur_word==NULL){
                error_exit("Realloc faile in tools add_to_result");
            }
        }
        strcpy(&result->cur_word[result->current_wrote],first_word);
        result->current_wrote+=size_of_word+1;
        result->cur_word[result->current_wrote-1]=' ';//instead of '\0' add space
        first_word+=size_of_word+1;//go to the next word
    }
    // printf("!!!%s\n",result->cur_word);
    result->cur_word[result->current_wrote-1]='|';
    result->cur_word[result->current_wrote]='\0';
    result->current_wrote+=0;
}

node_list* create_list(){
    node_list* newnode;
    newnode=malloc(sizeof(node_list));
    newnode->node=NULL;
    newnode->previous=NULL;
    newnode->position=-1;
    return newnode;
}

node_list* new_node_list(trie_node* trieNode,int position,node_list* previous){
    node_list* newnode;
    newnode=malloc(sizeof(node_list));
    newnode->node=trieNode;
    newnode->position=position;
    newnode->previous=previous;
    return newnode;
}

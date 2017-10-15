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
    free(*result);
    *result=NULL;
}

void add_to_result(result_of_search* result,char* the_word){
    result->num_of_results++;
    int size_of_word = strlen(the_word);
    while( size_of_word + 2 + result->current_wrote > result->current_size){
        printf("we need to realloc %d->%d(+%d)\n",result->current_size,2*result->current_size,size_of_word );
        //we need to make it bigger
        result->current_size*=2;
        result->cur_word=realloc(result->cur_word, result->current_size);
        if(result->cur_word==NULL){
            error_exit("Realloc faile in tools add_to_result");
        }
    }
    strcpy(&result->cur_word[result->current_wrote], the_word);
    result->cur_word[result->current_wrote+size_of_word]='|';
    result->cur_word[result->current_wrote+size_of_word+1]='\0';
    result->current_wrote+=size_of_word+1;
}

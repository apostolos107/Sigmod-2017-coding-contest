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

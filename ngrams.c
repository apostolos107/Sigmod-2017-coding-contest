#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"
// #include "tools.h"

int main (void)
{
  char * buf;
  size_t size=128;

  buf = malloc(sizeof(char)*size);
  trie * mytree = malloc(sizeof(trie));
  mytree->root = init_trie();
  // while(getline(&buf, &size, stdin) != -1)
  // {
  //     buf[strlen(buf)-1] = '\0';
  //     printf("%d\n", insert_ngram(mytree, buf));
  // }
  int i;
  for (i = 0; i < 5; i++)
  {
      getline(&buf, &size, stdin);
      buf[strlen(buf)-1] = '\0';
      printf("%d\n", insert_ngram(mytree, buf));
  }

  for (i = 0; i < 2; i++)
  {
      getline(&buf, &size, stdin);
      buf[strlen(buf)-1] = '\0';
      printf("%d\n", delete_ngram(mytree, buf));
  }

  for (i = 0; i < 5; i++)
  {
      getline(&buf, &size, stdin);
      buf[strlen(buf)-1] = '\0';
      printf("%d\n", insert_ngram(mytree, buf));
  }
  // int count = count_words(buf);
  // printf("Total words are %d, sentence is %s\n", count, buf);

  free(buf);
  return 0;
}

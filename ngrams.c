#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"
#include "trie.h"

int main(){
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
  while (1) {
      /* code */
      for (i = 0; i < 2; i++)
      {
          getline(&buf, &size, stdin);
          buf[strlen(buf)-1] = '\0';
          printf("%d\n", insert_ngram(mytree, buf));
      }

      for (i = 0; i < 2; i++)
      {
          getline(&buf, &size, stdin);
          buf[strlen(buf)-1] = '\0';
          printf("%d\n", trie_delete(mytree->root, buf));
      }
  }

  // int count = count_words(buf);
  // printf("Total words are %d, sentence is %s\n", count, buf);

  free(buf);
  return 0;

}

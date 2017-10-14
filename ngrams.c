#include <stdio.h>
#include <stdlib.h>
// #include <string.h>

#include "trie.h"
#include "tools.h"

int main (void)
{
  char * buf;
  size_t size=128;

  buf = malloc(sizeof(char)*size);

  getline(&buf, &size, stdin);
  int count = count_words(buf);
  printf("Total words are %d, sentence is %s\n", count, buf);

  free(buf);
  return 0;
}

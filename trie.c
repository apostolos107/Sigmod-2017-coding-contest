#include <stdio.h>
#include <stdlib.h>
// #include <string.h>

#include "trie.h"
#include "tools.h"
trie_node * init_trie()
{
  trie_node * node = create_trie_node();

  if(node == NULL)
    error_exit("Malloc Failure");

  node->word = malloc(1*sizeof(char));
  node->word[0] = '\0';

  return node;
}

trie_node* create_trie_node()
{
  trie_node * node = malloc(sizeof(trie_node));

  if(node == NULL)
    error_exit("Malloc Failure");

  node->is_final = 'N';
  node->current_children = 0;
  node->max_children = NUMBER_OF_CHILDREN;

  return node;
}

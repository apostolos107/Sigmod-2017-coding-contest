#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "trie.h"

int main(){
    trie * mytree = malloc(sizeof(trie));
    mytree->root = init_trie();
    assert(mytree!=NULL);
    assert(mytree->root!=NULL);

    return 0;
}

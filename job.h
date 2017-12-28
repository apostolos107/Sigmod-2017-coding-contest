#ifndef __JOB__
#define __JOB__

#define QUERY 'Q'

#include "tools.h"
#include "trie.h"

typedef struct job{
    char type;
    char* ngram;
    int print_position;
    int current_version;
    result_of_search* results;
    trie* my_trie;
}job;


#endif

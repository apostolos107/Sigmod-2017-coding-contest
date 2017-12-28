#ifndef __JOB__
#define __JOB__

#define QUERY 'Q'

#include "tools.h"
#include "trie.h"

typedef struct job{
    char type;
    char* ngram;
    int current_version;
    result_of_search* results;
    trie* my_trie;
    heap* my_heap;
}job;

// void update_job(job* my_job,char type,char* ngram,int version);
void update_job(job* my_job,char type,char* ngram,int version, trie* my_trie, heap* my_heap);

#endif

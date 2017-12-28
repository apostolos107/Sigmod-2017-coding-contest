#include "job.h"
#include "trie.h"


void update_job(job* my_job,char type,char* ngram,int version, trie* my_trie, heap* my_heap){
    my_job->current_version=version;
    my_job->ngram = copy_string(ngram);
    my_job->type= type;
    my_job->my_trie = my_trie;
    my_job->my_heap = my_heap;

}

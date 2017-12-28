#include "job.h"

job* create_job(char type,char* ngram,int version){
    job* my_job  = malloc(sizeof(job));
    my_job->current_version=version;
    my_job->ngram = ngram;
    my_job->type =type;
    return my_job;
}

#include "job.h"


void update_job(job* my_job,char type,char* ngram,int version){
    my_job->current_version=version;
    my_job->ngram = copy_string(ngram);
    my_job->type= type;
}

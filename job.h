#ifndef __JOB__
#define __JOB__

#define QUERY 'Q'

#include "tools.h"

typedef struct job{
    char type;
    char* ngram;
    int print_position;
    int current_version;
    result_of_search* results;
}job;


#endif

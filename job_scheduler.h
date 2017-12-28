#ifndef __JOB_SCHEDULER__
#define __JOB_SCHEDULER__

#include <pthread.h>
#include <stdlib.h>
#include "job.h"

#define JOBS_AMOUNT 30
#define THREADS_AMOUNT 10

typedef struct queue{
    int size;//the size of queue
    int amount_of_jobs;//the amount of jobs
    int position;//the first job to take
    job* my_jobs;
}queue;

typedef struct job_scheduler{
    pthread_t * threads;
    pthread_mutex_t mut_get_a_job;
    pthread_cond_t cond_get_a_job;

    pthread_mutex_t mut_finished_f;
    pthread_cond_t cond_finished_f;


    queue* my_queue;
    int threads_amount;
}job_scheduler;

queue* create_queue();
job_scheduler* initialize_scheduler();
void submit_job(job_scheduler* my_scheduler,job* myjob);
void execute_all_jobs(job_scheduler*);
void wait_all_tasks_finish(job_scheduler*);
void clean_job_table(job_scheduler*);
void destroy_job_scheduler(job_scheduler** myjob_scheduler);
job* give_me_job(job_scheduler*);

#endif

#include "job_scheduler.h"

queue* create_queue(){
    queue* myqueue;
    myqueue=malloc(sizeof(queue));
    myqueue->size=JOBS_AMOUNT;
    myqueue->amount_of_jobs=0;
    myqueue->position=0;
    myqueue->my_jobs=malloc(sizeof(job)*myqueue->size);
    return myqueue;
}

job_scheduler* initialize_scheduler(){
    job_scheduler* my_job_scheduler;
    my_job_scheduler=malloc(sizeof(job_scheduler));
    my_job_scheduler->threads_amount=THREADS_AMOUNT;
    my_job_scheduler->threads=malloc(sizeof(pthread_t)*my_job_scheduler->threads_amount);
    int i;
    // for(i=0 ; i< my_job_scheduler->threads_amount ; i++ ){
    //     pthread_create(&my_job_scheduler->threads[i],NULL,job,args );
    // }
    // pthread_mutex_init(&my_job_scheduler->mutex, 0);

    my_job_scheduler->my_queue=create_queue();
    return my_job_scheduler;
}

void execute_all_jobs(job_scheduler* my_scheduler){
    return;
}

void wait_all_tasks_finish(job_scheduler* my_scheduler){
    return;
}

job* give_me_job(job_scheduler* my_scheduler){
    queue* my_queue = my_scheduler->my_queue;
    if(my_queue->amount_of_jobs==my_queue->size){
        my_queue->size+=JOBS_AMOUNT;
        my_queue->my_jobs=realloc(my_queue->my_jobs,sizeof(job)*(my_queue->size));
    }
    my_queue->amount_of_jobs++;
    return &my_queue->my_jobs[my_queue->amount_of_jobs-1];
}

void submit_job(job_scheduler* my_scheduler,job* myjob){
    my_scheduler->my_queue->my_jobs[my_scheduler->my_queue->amount_of_jobs-1]=*myjob;
}

void clean_job_table(job_scheduler* my_scheduler){
    queue* my_queue = my_scheduler->my_queue;
    int i ;
    for(i = 0 ; i < my_queue->amount_of_jobs ; i++){
        free(my_queue->my_jobs[i].ngram);
        delete_result(&my_queue->my_jobs[i].results);
    }
    my_queue->amount_of_jobs=0;
    my_queue->position=0;
    my_queue->size=JOBS_AMOUNT;
}

void destroy_job_scheduler(job_scheduler** myjob_scheduler){
    free((*myjob_scheduler)->my_queue->my_jobs);
    free((*myjob_scheduler)->my_queue);
    free(*myjob_scheduler);
}

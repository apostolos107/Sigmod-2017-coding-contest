#include "job_scheduler.h"
#include "trie.h"
#include "job.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void *scheduler_worker(void* arg_scheduler);

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
    pthread_mutex_init(&my_job_scheduler->mut_get_a_job, 0);
    pthread_mutex_init(&my_job_scheduler->mut_finished_f, 0);
    pthread_mutex_init(&my_job_scheduler->mut_heap_update, 0);

    pthread_cond_init(&my_job_scheduler->cond_get_a_job, 0);
    pthread_cond_init(&my_job_scheduler->cond_finished_f, 0);
    pthread_cond_init(&my_job_scheduler->cond_heap_update, 0);

    my_job_scheduler->heap_busy = 0;//noone is writting on the heap
    my_job_scheduler->finished_jobs = 0;
    my_job_scheduler->exit_programm = 0;

    my_job_scheduler->my_queue=create_queue();

    for(i=0 ; i< my_job_scheduler->threads_amount ; i++ ){
        pthread_create(&my_job_scheduler->threads[i], NULL, scheduler_worker, (void*) my_job_scheduler );
    }

    return my_job_scheduler;
}

void execute_all_jobs(job_scheduler* my_scheduler){
    if(my_scheduler->my_queue->amount_of_jobs==0){
        return;
    }
    pthread_cond_signal(&my_scheduler->cond_get_a_job);
    return;
}

void wait_all_tasks_finish(job_scheduler* my_scheduler){
    if(my_scheduler->my_queue->amount_of_jobs==0){
        return;
    }
    pthread_mutex_lock(&my_scheduler->mut_finished_f);
    while (my_scheduler->finished_jobs<my_scheduler->my_queue->amount_of_jobs) {
        pthread_cond_wait(&my_scheduler->cond_finished_f, &my_scheduler->mut_finished_f);
    }
    pthread_mutex_unlock(&my_scheduler->mut_finished_f);
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
    my_scheduler->finished_jobs=0;
}

void destroy_job_scheduler(job_scheduler** my_job_scheduler){
    (*my_job_scheduler)->exit_programm=1;
    pthread_cond_signal(&(*my_job_scheduler)->cond_get_a_job);

    for (size_t i = 0; i < (*my_job_scheduler)->threads_amount; i++) {
        pthread_join((*my_job_scheduler)->threads[i],NULL);
    }

    pthread_mutex_destroy(&(*my_job_scheduler)->mut_finished_f);
    pthread_mutex_destroy(&(*my_job_scheduler)->mut_get_a_job);
    pthread_mutex_destroy(&(*my_job_scheduler)->mut_heap_update);

    pthread_cond_destroy(&(*my_job_scheduler)->cond_finished_f);
    pthread_cond_destroy(&(*my_job_scheduler)->cond_get_a_job);
    pthread_cond_destroy(&(*my_job_scheduler)->cond_heap_update);

    free((*my_job_scheduler)->my_queue->my_jobs);
    free((*my_job_scheduler)->my_queue);
    free(*my_job_scheduler);
}
void *scheduler_worker(void* arg_scheduler){
    job_scheduler* scheduler = (job_scheduler*) arg_scheduler;
    while(1){
        int cur_pos_working = -1;

        //get a job
        pthread_mutex_lock(&scheduler->mut_get_a_job);
        while( scheduler->my_queue->position>=scheduler->my_queue->amount_of_jobs && scheduler->exit_programm==0){
            pthread_cond_wait(&scheduler->cond_get_a_job, &scheduler->mut_get_a_job);
        }
        if(scheduler->exit_programm==1){
            pthread_cond_signal(&scheduler->cond_get_a_job);
            pthread_mutex_unlock(&scheduler->mut_get_a_job);
            pthread_exit((void*) 0);
        }

        cur_pos_working = scheduler->my_queue->position;//get the position
        scheduler->my_queue->position++;//wake up the next one
        pthread_cond_signal(&scheduler->cond_get_a_job);
        pthread_mutex_unlock(&scheduler->mut_get_a_job);


        //run the Q
        job* cur_job = &scheduler->my_queue->my_jobs[cur_pos_working];
        cur_job->results = search(cur_job->my_trie, cur_job->ngram ,cur_job->my_heap, cur_job->current_version);


        //out
        pthread_mutex_lock(&scheduler->mut_heap_update);
        while (scheduler->heap_busy!=0) {
            pthread_cond_wait(&scheduler->cond_heap_update, &scheduler->mut_heap_update);
        }
        scheduler->heap_busy=1;

        scheduler->finished_jobs++;
        scheduler->heap_busy=0;
        if(scheduler->finished_jobs==scheduler->my_queue->amount_of_jobs){
            //wake up main
            pthread_cond_signal(&scheduler->cond_finished_f);
        }
        pthread_cond_signal(&scheduler->cond_heap_update);
        pthread_mutex_unlock(&scheduler->mut_heap_update);
    }


}

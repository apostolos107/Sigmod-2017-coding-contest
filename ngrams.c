#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"
#include "trie.h"
#include "heap.h"
#include "job_scheduler.h"

#define CHAR_BUFFER_SIZE 1024


int main (int argc, char* argv[])
{
    char * buf;//the buffer that we will use for reading lanes
    size_t size=CHAR_BUFFER_SIZE;
    buf = malloc(sizeof(char)*size);//alocate memory for the buffer that
    trie * my_triee = init_trie();

    char* query_filename=NULL;
    char* init_filename=NULL;
    char last_function='0';
    int i;
    for (i = 1; i < argc; i++) {
        if( strcmp(argv[i],"-i")==0 ){
            if(i+1>=argc){
                error_exit("Bad arguments for -i");
            }
            i++;
            init_filename=argv[i];
        }else if(strcmp(argv[i],"-q")==0){
            if(i+1>=argc){
                error_exit("Bad arguments for -q");
            }
            i++;
            query_filename=argv[i];
        }else{
            printf("Uknown argument {%s}\n", argv[i]);
            error_exit("Bad arguments");
        }
    }

    //if there is init file open it
    FILE* read_from=stdin;
    int is_static=0;//is it a static file
    if(init_filename!=NULL){
        //open the file and make the init
        FILE* init_file = fopen(init_filename, "r");
        if(init_file==NULL){
            error_exit("Not good init File");
        }
        init_filename=NULL;
        getline(&buf, &size, init_file);
        //checks if it's a static file
        if( strcmp(buf, "STATIC\n")==0 )
        {
            is_static=1;
        }
        else
        {
            is_static=0;
        }

        while(1){
            int chars_read=0;
            chars_read=getline(&buf, &size, init_file);
            if(chars_read>0){
                buf[chars_read-1]='\0';//delete the \0
                // printf("---Add{%s}\n", buf);
                last_function = 'A';
                insert_ngram(my_triee, buf);
            }else{
                break;
            }
        }
        fclose(init_file);
    }
    if(query_filename!=NULL){
        //if there is query file
        FILE* query_file = fopen(query_filename, "r");
        if(query_file==NULL){
            error_exit("Not good query file");
        }
        query_filename=NULL;
        read_from=query_file;
    }else{
        read_from=stdin;
    }

    int count=0;
    int chars_read=0;
    char* the_word=NULL;
    heap* my_heap = heap_create();
    if( is_static==1 ){
        //if it's a static file, compress before continue
        trie_compress(my_triee);
    }
//create job scheduler

    job_scheduler* my_scheduler = initialize_scheduler();
    while(1){
        chars_read=getline(&buf, &size, read_from);
        if(chars_read==-1){
            //exit or switch beetwen query file to stdin
            if(read_from==stdin){
                // printf("Bye\n");
                //that means exit
                break;
            }else{
                // that means that we finshed with query file
                fclose(read_from);
                read_from=stdin;
                continue;
            }
            //maybe we will need to excecute somthing like F first
        }
        //it removes the \n at the end and adds a \0
        buf[chars_read-1]='\0';
        if(buf[0]=='Q'){
            the_word=&buf[2];
            if (last_function != 'Q')
            {
                /* code */
                update_version(my_triee);
            }
            last_function = 'Q';
            job* new_job = give_me_job(my_scheduler);
            update_job(new_job,'Q',the_word,my_triee->version,my_triee,my_heap);
            submit_job(my_scheduler,new_job);
            // printf("---Question{%s}\n", the_word);
        }else
        if(buf[0]=='A'){
            the_word= &buf[2];
            if (last_function == 'Q')
            {
                /* code */
                update_version(my_triee);
            }
            last_function = 'A';
            // printf("---Add{%s}\n", the_word);
            insert_ngram(my_triee, the_word);
        }
        else if(buf[0]=='D'){
            the_word= &buf[2];
            if (last_function == 'Q')
            {
                /* code */
                update_version(my_triee);
            }
            last_function = 'D';
            // printf("---Delete{%s}\n", the_word);
            delete_ngram(my_triee, the_word);

        }else if(buf[0]=='F'){
            execute_all_jobs(my_scheduler);
            wait_all_tasks_finish(my_scheduler);
            int j;
            result_of_search* result;
            queue* my_queue = my_scheduler->my_queue;
            for(j = 0 ; j < my_queue->amount_of_jobs; j++){
                result = my_queue->my_jobs[j].results;
                if(result->num_of_results!=0){
                    result->cur_word[strlen(result->cur_word)-1]='\0';
                    // printf("====%s\n",result->cur_word);
                    printf("%s\n",result->cur_word);
                }else{
                    // printf("====-1\n");
                    printf("-1\n");
                }
            }
            clean_job_table(my_scheduler);
            int k=0;
            sscanf(buf, "F %d",&k);
            if(k!=0){
                // printf("Top: ");
                heap_print_top_k(my_heap, k);//print
            }
            heap_destroy(&my_heap);
            my_heap = heap_create();
            // printf("---A wild F appeared\n");
        }
    }
    trie_clean(&my_triee);
//    hash_clean(&my_triee->children);
    free(my_triee);
    destroy_job_scheduler(&my_scheduler);
//free whatever is allocated
    heap_destroy(&my_heap);
    free(buf);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"
#include "trie.h"

#define CHAR_BUFFER_SIZE 128
int main (int argc, char* argv[])
{
    char * buf;//the buffer that we will use for reading lanes
    size_t size=CHAR_BUFFER_SIZE;

    buf = malloc(sizeof(char)*size);//alocate memory for the buffer that
    trie * mytree = malloc(sizeof(trie));
    mytree->root = init_trie();

    char* init_filename=NULL;
    char* query_filename=NULL;

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
    if(init_filename!=NULL){
    //open the file and make the read_from this file
    FILE* init_file = fopen(init_filename, "r");
    if(init_file==NULL){
        error_exit("Not good init File");
    }
    init_filename=NULL;
    read_from=init_file;
    }else if(query_filename!=NULL){
        //if there is no init file use the query file if exists ALONE
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
    while(1){
        chars_read=getline(&buf, &size, read_from);
        if(chars_read==-1){
            //or switch beetwen file to stdin
            if(read_from==stdin){
                printf("Bye\n");
                //that means exit
                break;
            }else{
                // that means that we finshed with a file, but which?
                fclose(read_from);
                if(query_filename==NULL){
                    read_from=stdin;
                }else{
                    read_from=fopen(query_filename, "r");
                    if(read_from==NULL){
                        read_from=stdin;
                    }
                    query_filename=NULL;
                }
                continue;
            }
            //maybe we will need to excecute somthing like F first
        }
        //it removes the \n at the end and adds a \0
        buf[chars_read-1]='\0';
        if(buf[0]=='Q'){
            the_word=&buf[2];
            printf("---Question{%s}\n", the_word);
            result_of_search* result = search(mytree,the_word);
            if(result->num_of_results!=0){
                printf("^^^[%s]\n",result->cur_word);
            }else{
                printf("^^^-1\n");
            }
        }else if(buf[0]=='A'){
            the_word= &buf[2];
            printf("---Add{%s}\n", the_word);
            insert_ngram(mytree, the_word);
        }else if(buf[0]=='D'){
            the_word= &buf[2];
            printf("---Delete{%s}\n", the_word);
            delete_ngram(mytree, the_word);

        }else if(buf[0]=='F'){
            printf("---A wild F appeared\n");
        }else{
            printf("---I don't know what is this{%s}{%d}\n",buf,chars_read);
        }
    }
    trie_clean(mytree);
//free whateve is allocated
    free(buf);
    return 0;
}

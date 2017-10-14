#include <stdio.h>
#include <stdlib.h>
// #include <string.h>

#include "trie.h"
#include "tools.h"

#define CHAR_BUFFER_SIZE 128
int main (int argc, char* argv[])
{
  char * buf;//the buffer that we will use for reading lanes
  size_t size=CHAR_BUFFER_SIZE;

  buf = malloc(sizeof(char)*size);

  char* init_filename=NULL;
  char* query_filename=NULL;

  int i;
  for (i = 1; i < argc; i++) {
    if(argv[i]=="-i"){
      if(argc+1>=i){
        error_exit("Bad arguments for -i");
      }
      init_filename=argv[i+1];
    }else if(argv[i]=="-q"){
      if(argc+1>=i){
        error_exit("Bad arguments for -q");
      }
      query_filename=argv[i+1];
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
    FILE* query_file = fopen(query_file, "r");
    if(query_file!=NULL){
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

    chars_read=getline(&buf, &size, stdin);

    if(chars_read==-1){
      printf("Nothing read, I am breaking/changing\n");
      //or switch beetwen file to stdin
      if(read_from==stdin){
        printf("Bye\n");
        //that means exit
      }else{
        // that means that we finshed with a file, but which?
        printf("end with a file, now use the next or what?\n");
        fclose(read_from);
        if(query_filename==NULL){
          read_from=stdin;
        }else{
          read_from=fopen(query_filename, "r");
          if(read_from==NULL){
            error_exit("Not good query file but it's late now :P read from stdin");
            read_from=stdin;
          }
        }
      }
      //maybe we will need to excecute somthing like F first
      break;
    }
    if(buf[0]=='Q'){
      the_word=&buf[1];
      printf("Question{%s}\n", the_word);

    }else if(buf[0]=='A'){
      the_word= &buf[1];
      printf("Add{%s}\n", the_word);

    }else if(buf[0]=='D'){
      the_word= &buf[1];
      printf("Delete{%s}\n", the_word);

    }else if(buf[0]=='F'){
      printf("An wild F apperead\n");

    }else{
      printf("I don't know what is this{%s}{%d}\n",buf,chars_read);

    }
  }

  free(buf);
  return 0;
}

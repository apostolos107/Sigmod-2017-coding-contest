#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "tools.h"
#include <string.h>
#define MAX_DEPTH 40

int cmp_heap_node(heap_node* heap_node1, heap_node* heap_node2){
    if(heap_node1->appeared < heap_node1->appeared){
        return -1;
    }else if(heap_node1->appeared > heap_node1->appeared){
        return 0;
    }else{
        return strcmp(heap_node1->content, heap_node2->content);
    }
}

heap_node* create_node(){
    heap_node* new_node = malloc(sizeof(heap_node));
    new_node->left=NULL;
    new_node->right=NULL;
    new_node->parrent=NULL;
    new_node->content=NULL;
    new_node->appeared=0;
    return new_node;
}

heap* heap_create(){
    heap* new_heap;
    new_heap = malloc(sizeof(heap));
    new_heap->root=NULL;//there is no root
    new_heap->number_of_nodes=0;//we have no childrens
    return new_heap;
}

void heapify(heap* the_heap, heap_node* start_node){
    int temp;
    heap_node *parrent;
    heap_node *up_l,*up_r,*temp1,*temp2;
    heap_node *do_l,*do_r;
    parrent=start_node->parrent;
    if( cmp_heap_node(start_node, parrent)>1 ){
        do_l=start_node->left;
        do_r=start_node->right;
        up_l=parrent->left;
        up_r=parrent->right;

        //set the kids of the start node if they have to show to the parrent
        if( start_node->left !=NULL ){
            start_node->left->parrent=parrent;
        }
        if( start_node->right !=NULL ){
            start_node->right->parrent=parrent;
        }

        //set the parent's parent left or right to show to the correct node
        if(parrent->parrent!=NULL){//eftasa sthn riza
            if(parrent->parrent->left==parrent){
                parrent->parrent->left=start_node;
            }else{
                parrent->parrent->right=start_node;
            }
        }else{
            the_heap->root=start_node;
        }
        //fix the pointers in
        if(parrent->left==start_node){
            if(parrent->right!=NULL) parrent->right->parrent=start_node;//an uparxei
            parrent->left=do_l;
            parrent->right=do_r;
            start_node->parrent=parrent->parrent;
            start_node->left=parrent;
            start_node->right=up_r;
        }else if(parrent->right==start_node){
            if(parrent->left!=NULL) parrent->left->parrent=start_node;//an uparxei
            parrent->right=do_r;
            parrent->left=do_l;
            start_node->parrent=parrent->parrent;
            start_node->left=up_l;
            start_node->right=parrent;
        }
        parrent->parrent=start_node;
        heapify(the_heap,start_node);//to ksanakalw alla to node tr exei anebei
    }else{//all iz well
        return;
    }
}

heap_node* heap_insert(heap* the_heap, char* word){
    int last_step;
    heap_node* cur_node;
    if (the_heap->number_of_nodes==0){
        //if it's the first node in the heap
        cur_node=the_heap->root=create_node();//all the pointers are NULL
        cur_node->appeared=0;
        cur_node->content=copy_string(word);
        the_heap->number_of_nodes++;
        return cur_node;
    }
    cur_node=find_the_parent(the_heap,&last_step,the_heap->number_of_nodes+1);
    heap_node *new_node=create_node();//create the new node
    new_node->parrent=cur_node;
    new_node->content=copy_string(word);
    if(last_step==0){
        cur_node->left=new_node;
    }else if(last_step==1){
        cur_node->right=new_node;
    }
    the_heap->number_of_nodes++;
    heapify(the_heap,new_node);
    return new_node;
}

char* heap_get_top(heap* the_heap)
{
    //find the last node
    int last_step;
    heap_node* first_node=the_heap->root;
    heap_node* last_node=find_the_parent(the_heap,&last_step,the_heap->number_of_nodes);
    if(last_step  == 1)
    {
        last_node=last_node->right;
    }
    else if(last_step == 0)
    {
        last_node=last_node->left;
    }
    //swap the first with the last
    first_node->parrent = last_node->parrent;
    last_node->parrent = NULL;
    last_node->left = first_node->left;
    last_node->right = first_node->right;
    first_node->right = NULL ;
    first_node-> left = NULL ;

    char* return_string;
    return_string = malloc((strlen(first_node->content)+1)*sizeof(char));
    strcpy(return_string, first_node->content);

    //delete the last node (it was the first)
    if(last_step  == 1)
    {
        first_node->parrent->right = NULL;
    }
    else if(last_step == 0)
    {
        first_node->parrent->left = NULL;
    }
    free(first_node->content);
    free(first_node);
    return return_string;
}

heap_node* find_the_parent(heap* the_heap,int *last_step,int int_cur_node)
{
    //we calculate the best path trhough this algorithm
        int step[MAX_DEPTH];//a stack like array
        int depth=0;//stack gia tis kinhseis anadromika

        while(int_cur_node>1)
        {
            step[depth]=int_cur_node%2;//1 means right , 0 means left
            int_cur_node=int_cur_node/2;//do the same for the parent
            depth++;
        }
    //we have find the path and now we must go to the node
        int i;
        heap_node* cur_node;
        cur_node=the_heap->root;//begin from the root
        for(i=depth-1;i>0;i--)
        {//for all (exept the first one)
            if(step[i]==0)
            {
                cur_node=cur_node->left;
            }
            else
            {
                cur_node=cur_node->right;
            }
        }
        *last_step=step[i];
        return cur_node;
}

// heap_search(heap* the_heap, char* word){
//
// }

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
    heap_node* cur_node;
    if (the_heap->number_of_nodes==0){
        //if it's the first node in the heap
        cur_node=the_heap->root=create_node();//all the pointers are NULL
        cur_node->appeared=0;
        cur_node->content=copy_string(word);
        the_heap->number_of_nodes++;
        return cur_node;
    }

//we calculate the best path trhough this algorithm
    int int_cur_node;//a var to help calculate the path
    int step[MAX_DEPTH];//a stack like array
    int depth=0;//stack gia tis kinhseis anadromika

    int_cur_node=the_heap->number_of_nodes+1;//start from the first free
    while(int_cur_node>1){
        step[depth]=int_cur_node%2;//1 means right , 0 means left
        int_cur_node=int_cur_node/2;//do the same for the parent
        depth++;
    }
//we have find the path and now we must go to the node
    int i;
    cur_node=the_heap->root;//begin from the root
    for(i=depth-1;i>0;i--){//for all (exept the first one)
        if(step[i]==0){
            cur_node=cur_node->left;
        }else{
            cur_node=cur_node->right;
        }
    }

    heap_node *new_node=create_node();//create the new node
    new_node->parrent=cur_node;
    new_node->content=copy_string(word);
    if(step[i]==0){
        cur_node->left=new_node;
    }else if(step[i]==1){
        cur_node->right=new_node;
    }
    the_heap->number_of_nodes++;
    heapify(the_heap,new_node);
    return new_node;
}

heap_node* heap_search(heap_node* start_node, char* word){
    heap_node* cur_node = start_node;
    if(cur_node!=NULL){
        int cmp_val = strcmp(cur_node->content , word);
        if( cmp_val==0 ){
            //if found return this
            return cur_node;
        }else if(cmp_val==-1){
            //if it's smaller than the root
            //no need to go deeper (pruning)
            return NULL;
        }else if(cmp_val==1){
            //it's children of one of the kids
            heap_node* left_result,right_result;
            left_result = heap_search(cur_node->left, word);
            if(left_result!=NULL){
                return left_result;
            }else{
                return heap_search(cur_node->left, word);
            }
        }

    }
    return NULL;
}

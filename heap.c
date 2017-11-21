#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "tools.h"
#include <string.h>
#define MAX_DEPTH 40

typedef struct heap_list_node {
    heap_node* the_entrie;
    struct heap_list_node* next;
}heap_list_node;

int cmp_heap_node(heap_node* heap_node1, heap_node* heap_node2);

char* heap_get_top(heap* the_heap);//returns the most finded word

heap_node* heap_delete_top(heap* the_heap);//deletes the heap root item

heap_node* find_the_parent(heap* the_heap,int*,int) ;

heap_node* heap_search(heap_node* start_node, char* word);

void heap_swap_nodes(heap* the_heap, heap_node* heap_1, heap_node* heap_2);

int cmp_heap_node(heap_node* heap_node1, heap_node* heap_node2){
    if(heap_node1==NULL || heap_node1==NULL){
        return 0;
    }
    if(heap_node1->appeared < heap_node2->appeared){
        return -1;
    }else if(heap_node1->appeared > heap_node2->appeared){
        return 1;
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
    new_node->appeared=1;
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
    if(start_node==NULL || start_node->parrent==NULL){
        return;
    }
    parrent=start_node->parrent;
    if( cmp_heap_node(start_node, parrent)>0 ){
        char* temp_str;
        int temp_int;
        heap_swap_nodes(the_heap, start_node, parrent);

        // temp_str=start_node->content;
        // start_node->content = parrent->content;
        // parrent->content = temp_str;
        //
        // temp_int = start_node->appeared;
        // start_node->appeared = parrent->appeared;
        // parrent->appeared = temp_int;
        heapify(the_heap,parrent);//now heapify the parrent

        // do_l=start_node->left;
        // do_r=start_node->right;
        // up_l=parrent->left;
        // up_r=parrent->right;
        //
        // //set the kids of the start node if they have to show to the parrent
        // if( start_node->left !=NULL ){
        //     start_node->left->parrent=parrent;
        // }
        // if( start_node->right !=NULL ){
        //     start_node->right->parrent=parrent;
        // }
        //
        // //set the parent's parent left or right to show to the correct node
        // if(parrent->parrent!=NULL){//eftasa sthn riza
        //     if(parrent->parrent->left==parrent){
        //         parrent->parrent->left=start_node;
        //     }else{
        //         parrent->parrent->right=start_node;
        //     }
        // }else{
        //     the_heap->root=start_node;
        // }
        // //fix the pointers in
        // if(parrent->left==start_node){
        //     if(parrent->right!=NULL) parrent->right->parrent=start_node;//an uparxei
        //     parrent->left=do_l;
        //     parrent->right=do_r;
        //     start_node->parrent=parrent->parrent;
        //     start_node->left=parrent;
        //     start_node->right=up_r;
        // }else if(parrent->right==start_node){
        //     if(parrent->left!=NULL) parrent->left->parrent=start_node;//an uparxei
        //     parrent->right=do_r;
        //     parrent->left=do_l;
        //     start_node->parrent=parrent->parrent;
        //     start_node->left=up_l;
        //     start_node->right=parrent;
        // }
        // parrent->parrent=start_node;
        //we don't swap the pointers, we spaw the data in the node
        // heapify(the_heap,start_node);//now heapify the start node that is moved up
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
        cur_node->appeared=1;
        cur_node->content=copy_string(word);
        the_heap->number_of_nodes++;
        return cur_node;
    }
    //find the node that we will insert the new entry
    cur_node = heap_search(the_heap->root, word);//search if the words already exists
    if(cur_node!=NULL){
        //if the words exists increase and heapify
        cur_node->appeared++;
        heapify(the_heap,cur_node);
        return cur_node;
    }else{
        //find where should be insert
        cur_node=find_the_parent(the_heap,&last_step,the_heap->number_of_nodes+1);
        heap_node *new_node=create_node();//create the new node
        new_node->parrent=cur_node;
        new_node->content=copy_string(word);
        new_node->appeared=1;
        if(last_step==0){
            cur_node->left=new_node;
        }else if(last_step==1){
            cur_node->right=new_node;
        }
        the_heap->number_of_nodes++;
        heapify(the_heap,new_node);
        return new_node;
    }
}

void heap_swap_nodes(heap* the_heap, heap_node* heap_1, heap_node* heap_2){
    char* temp_str;
    int temp_int;
    /*swap the string*/
    temp_str = heap_1->content;
    heap_1->content = heap_2->content;
    heap_2->content = temp_str;

    /*swap the appeared value*/
    temp_int = heap_1->appeared;
    heap_1->appeared = heap_2->appeared;
    heap_2->appeared = temp_int;
}

// char* heap_get_top(heap* the_heap)
// {
//     //find the last node
//     int last_step;
//     heap_node* first_node=the_heap->root;
//     heap_node* last_node=find_the_parent(the_heap,&last_step,the_heap->number_of_nodes);
//     if(last_step  == 1)
//     {
//         last_node=last_node->right;
//     }
//     else if(last_step == 0)
//     {
//         last_node=last_node->left;
//     }
//     //swap the first with the last
//     // first_node->parrent = last_node->parrent;
//     // last_node->parrent = NULL;
//     // last_node->left = first_node->left;
//     // last_node->right = first_node->right;
//     // first_node->right = NULL ;
//     // first_node-> left = NULL ;
//     char* return_string;
//     int temp_int;//temp variables
//
//     return_string = first_node->content;
//     first_node->content = last_node->content;
//     first_node->appeared = last_node->appeared;//we don't care how many times appeared
//
//     // return_string = malloc((strlen(first_node->content)+1)*sizeof(char));
//     // strcpy(return_string, first_node->content);
//
//     //delete the last node (it was the first)
//     if(last_step  == 1)
//     {
//         last_node->parrent->right = NULL;
//     }
//     else if(last_step == 0)
//     {
//         last_node->parrent->left = NULL;
//     }
//     free(last_node);//just free the last node
//     the_heap->number_of_nodes--;
//     //remain heap by findin the new max
//     heap_node* cur_node = NULL;
//     cur_node = first_node;
//     do{
//         int cmp_left=0;//root with left
//         int cmp_right=0;//root with right
//         int cmp_left_with_right=0;//left with right
//     }while();
//     return return_string;//the string of the old first node
// }

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

heap_node* heap_search(heap_node* start_node, char* word){
    heap_node* cur_node = start_node;
    if(cur_node!=NULL){
        int cmp_val = strcmp(cur_node->content , word);
        if( cmp_val==0 ){
            //if found return this
            return cur_node;
        }else{
            //it's children of one of the kids
            heap_node* left_result,right_result;
            left_result = heap_search(cur_node->left, word);
            if(left_result!=NULL){
                return left_result;
            }else{
                return heap_search(cur_node->right, word);
            }
        }

    }
    return NULL;
}

void heap_list_add_node(heap_list_node** the_node,heap_node* new_entrie ){
    if(new_entrie==NULL){
        return;
    }

    //init the list node
    heap_list_node *new_node=malloc(sizeof(heap_list_node));
    new_node->the_entrie=new_entrie;
    new_node->next=NULL;

    heap_list_node* cur_node=*the_node;//start from the first node(argument)
    heap_list_node* prev_node=NULL;
    if(cur_node==NULL){//if it's NULL that means create the list
        *the_node=new_node;
        return ;
    }

//an den einai to prwto
    while(cur_node!=NULL){//prospelase olous tous kombous
        int cmp_val = cmp_heap_node(new_entrie, cur_node->the_entrie);
        if(cmp_val>0){//mexri na breis kati pou eiani mikrotero apo to kainourio
            break;
        }
        prev_node=cur_node;
        cur_node=cur_node->next;
    }//teliwnontas to kainourio tha prepei na mpei meta ton cur_node
    if(prev_node!=NULL){
        prev_node->next=new_node;
        new_node->next=cur_node;
    }else{
        //we changed the first one
        *the_node=new_node;
        new_node->next=cur_node;
    }
}

void heap_list_delete_list(heap_list_node** the_list){//eleutheronei ton xwro pou exei desmeutei gia thn lista
    heap_list_node *cur_node,*temp_node;
    cur_node=*the_list;
    while(cur_node!=NULL){
        temp_node=cur_node->next;
        free(cur_node);
        cur_node=temp_node;
    }
    *the_list=NULL;
}

void heap_print_top_k(heap* the_heap, int k){
    int printed_nodes = 0;
    heap_list_node *the_heap_list = NULL,*temp_list;
    heap_list_add_node(&the_heap_list, the_heap->root);//add the root to the list(initialize it)

    heap_node *left,*right;

    while (printed_nodes<k && printed_nodes<the_heap->number_of_nodes) {
        heap_node* cur_node;
        cur_node = the_heap_list->the_entrie;

        left=cur_node->left;
        right=cur_node->right;
        //take the first element and add left and right to the list with the results
        heap_list_add_node(&the_heap_list,left);
        heap_list_add_node(&the_heap_list,right);
        //update printed nodes
        printed_nodes++;
        //print the node
        printf("|%s(%d)\n\n", cur_node->content,cur_node->appeared);
        //bgale apo thn lista thn kefalh
        temp_list=the_heap_list;
        the_heap_list=the_heap_list->next;//move list to the next element
        free(temp_list);//free the first elemnt
    }
    if(the_heap_list!=NULL){
        heap_list_delete_list(&the_heap_list);
    }
}

void heap_destroy(heap** the_heap){
    void delete_sub_heap(heap_node *cur_node){
        if(cur_node==NULL){
            return ;
        }
        delete_sub_heap(cur_node->left);
        delete_sub_heap(cur_node->right);
        free(cur_node->content);
        free(cur_node);
    }

    delete_sub_heap( (*the_heap)->root );
    free(*the_heap);
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linkedListlib.h"

struct ListNode* reverseBetween(struct ListNode* head, int left, int right){
    struct ListNode* move = head;
    struct ListNode* prev = move;
    for(int i = 0; i < left-1; i++){
        prev = move;
        move = move->next;
    }
    struct ListNode* start,*start2;
    if(!move->next){
        return head;
    }else if (prev != move){
        start = prev;
        start2 = move;    
    }else{
        start = NULL;
        start2 = move;  
    }

    
    if (move){
        struct ListNode* temp = move->next;
        
        move->next = NULL;
        prev = move;
        move = temp; 
        for(int i = 0; i < right-left; i++){
            if(!move)break;
            temp = move->next;
            move->next = prev;
            prev = move;
            move = temp;
        }
    }
    if (start){
        start->next = prev;
        
    }else{
        start = prev;
        head = start;
        // return start;

    
    }
    if (move) start2->next = move;
    
    return head;
}

int main(){
    int l1[] = {1,2,3,4,5,6};
    struct ListNode* list1 = createList(l1,sizeof(l1)/sizeof(l1[0]));
    struct ListNode* list2 = reverseBetween(list1, 1, 2);
}
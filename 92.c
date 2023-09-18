#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* createList(int* l1,int len){
    struct ListNode* list1 = (struct ListNode*)calloc(1, sizeof(struct ListNode));
    struct ListNode* head = (struct ListNode*)calloc(1, sizeof(struct ListNode));
    if (len>0){
        list1->val = l1[0];
        // struct ListNode* temp = (struct ListNode*)calloc(1, sizeof(struct ListNode));
        list1->next = NULL;
        head = list1;
        // list1 = list1->next;
        for (int i = 1; i < len; i++){
            list1->next = (struct ListNode*)calloc(1, sizeof(struct ListNode));
            list1 = list1->next;
            list1->val = l1[i];
            list1->next = NULL;
        }

        list1 = head;
        return list1;
    }
    else{
        return NULL;
    }
}

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
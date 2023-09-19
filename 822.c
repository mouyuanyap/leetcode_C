#include <stdio.h>
#include <stdlib.h>
#include "linkedListlib.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* deleteDuplicates(struct ListNode* head){
    struct ListNode* move = head;
    struct ListNode* prev = NULL;
    while (move){
        if (move->next != NULL && move->val == move->next->val){
            struct ListNode* temp = move;
            while (temp && temp->val == move->val){
                temp = temp->next;
            }
            if (prev == NULL){
                head = temp;
                move = temp;
                continue;
            }else{
                prev->next = temp;
                
                move = temp;
                continue;
            }
        }
        prev = move;
        move = move->next;
    }
    return head;
}

int main(){
    int l1[] = {1,1,2,2};
    struct ListNode* list1 = createList(l1,sizeof(l1)/sizeof(l1[0]));
    deleteDuplicates(list1);
}
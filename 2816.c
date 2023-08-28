/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#include <stdio.h>
#include <stdlib.h>

 struct ListNode {
      int val;
      struct ListNode *next;
 };

struct ListNode* doubleIt(struct ListNode* head){
    int i = 0;
    struct ListNode* temp = head;
    struct ListNode* newHead = (struct ListNode*)calloc(1,sizeof(struct ListNode));
    while (head!= NULL){
        
        int d = head->val * 2;
        if (i==0){
            if (d/10 != 0){
                newHead->val = d/10;
                newHead->next = head;
            }
            else{
                newHead = head;
            }
        }else{
            if (d/10 != 0){
                temp->val = temp->val + d/10;
            }
        }
        head->val = d%10;
        temp = head;
        head = head->next;
        i+=1;
    }
    return newHead;
}
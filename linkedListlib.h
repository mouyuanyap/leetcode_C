#include <stdio.h>
#include <stdlib.h>

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
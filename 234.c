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

struct ListNode* findMid(struct ListNode* head){
    struct ListNode* fast = head->next;
    struct ListNode* slow = head;
    struct ListNode* temp;
    while (fast){
        temp = slow;
        slow = slow->next;
        if (fast->next){
            fast = fast->next->next;
        }else{
            break;
        }
        
    }
    temp -> next = NULL;
    return slow;
}


struct ListNode* reverseLL(struct ListNode* head){
    //old list being overwritten
    struct ListNode* currentNode = head;
    struct ListNode* prev;
    while (currentNode!=NULL){
        
        if (currentNode == head){
            struct ListNode* temp = currentNode->next;
            prev = currentNode;
            currentNode->next = NULL;
            currentNode = temp;
        }else{
            struct ListNode* temp = currentNode->next;
            currentNode->next = prev;
            prev = currentNode;
            currentNode = temp;
        }
    }
    return prev;

    // Original list not changed
    // struct ListNode* newList = (struct ListNode*)malloc(sizeof(struct ListNode));
    // struct ListNode* currentNode = head;
    // newList->val = currentNode->val;
    // currentNode = currentNode->next;
    // struct ListNode* currentNode2 = newList;
    // while (currentNode){
    //     struct ListNode* temp = (struct ListNode*)malloc(sizeof(struct ListNode));
    //     temp->val = currentNode->val;
    //     currentNode2->next = temp;
    //     currentNode2 = currentNode2->next;
    //     currentNode = currentNode->next;
    // }

    // currentNode = newList;
    // struct ListNode* prev;
    // struct ListNode* temp = currentNode->next;
    // prev = currentNode;
    // currentNode->next = NULL;
    // currentNode = temp;
    // while (currentNode!=NULL){
        
    //     struct ListNode* temp = currentNode->next;
    //     currentNode->next = prev;
    //     prev = currentNode;
    //     currentNode = temp;
        
    // }
    // return prev;
}

bool isPalindrome(struct ListNode* head){
    if (head->next==NULL) return true;
    struct ListNode* tail = findMid(head);
    tail = reverseLL(tail);
    struct ListNode* prev = head;
    while (head){
        if (head->val != tail->val) return false;
        head = head->next;
        tail = tail->next;
    }
    return true;

}



int main(){
    int l1[] = {1};
    struct ListNode* list1 = createList(l1,sizeof(l1)/sizeof(l1[0]));
    // struct ListNode* list2 = findMid(list1);
    if (isPalindrome(list1)){
        printf("true");
    }else{
        printf("false");
    }
}
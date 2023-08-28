#include <stdio.h>
#include <stdlib.h>

 struct ListNode {
     int val;
     struct ListNode *next;
 };

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2){
    struct ListNode* head = (struct ListNode*)calloc(1, sizeof(struct ListNode));
    struct ListNode* temp = (struct ListNode*)calloc(1, sizeof(struct ListNode));
    struct ListNode* move = (struct ListNode*)calloc(1, sizeof(struct ListNode));

    if (list1 != NULL && list2!=NULL){
        int i = 0;
        while(move!=NULL && temp!=NULL){
            if (i == 0){
                if (list1->val > list2->val){
                    head = list2;
                    move = list2;
                    temp = list1;
                    
                }else{
                    head = list1;
                    move = list1;
                    temp = list2;
                }
                
            }else{
                if (move->next == NULL){
                    move->next= temp;
                    break;
                }
                if (temp->val > move->next->val){
                    move = move -> next;
                }else{
                    struct ListNode* temp2 = (struct ListNode*)calloc(1, sizeof(struct ListNode));
                    temp2 = move->next;
                    move->next = temp;
                    move = move->next;
                    temp = temp2;
                    
                }
                
            }
            
            i+=1;
        }
        return head;
    }
    else if (list1 != NULL && list2==NULL){
        return list1;
    }
    else if (list1 == NULL && list2!=NULL){
        return list2;
    }
    
}

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

int main(){
    
    int l1[] = {2,4,5};
    int l2[] = {1,2,4};
    struct ListNode* list1 = createList(l1,sizeof(l1)/sizeof(l1[0]));
    struct ListNode* list2 = createList(l2,sizeof(l2)/sizeof(l2[0]));
    struct ListNode* list3 = mergeTwoLists(list1,list2);

}
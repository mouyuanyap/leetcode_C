#include <stdio.h>
#include <stdlib.h>
#include "binarySearchTree.h"

struct TreeNode* createNode(int val){
    struct TreeNode* node = (struct TreeNode* )malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct nodeStack{
    struct TreeNode* node;
    struct nodeStack* next;
}nodeStack;

struct TreeNode* constructMaximumBinaryTree(int* nums, int numsSize){
    struct nodeStack* head = NULL;
    struct TreeNode* newNode;
    struct nodeStack* temp;
    struct TreeNode* answer=NULL;
    for(int i = 0; i<numsSize; i++){
        if (head == NULL){
            head = (struct nodeStack*)malloc(sizeof(struct nodeStack));
            head->node = createNode(nums[i]);
            head->next = NULL;
        }
        else if(nums[i] > head->node->val){
            newNode = createNode(nums[i]);
            struct nodeStack* tempHead = head;
            struct nodeStack* newHead = head;
            while(tempHead->next!=NULL && tempHead->next->node->val < nums[i]){
                tempHead->next->node->right = tempHead->node;
                
                tempHead = tempHead->next;
                newHead = tempHead;
            }
            head = newHead;
            newNode->left = head->node;
            temp= (struct nodeStack*)malloc(sizeof(struct nodeStack));
            temp->node = newNode;
            temp->next = head->next;
            head = temp;
            printf("%d,",head->node->val);
        }
        else if(nums[i] < head->node->val){
            newNode = createNode(nums[i]);
            temp= (struct nodeStack*)malloc(sizeof(struct nodeStack));
            temp->node = newNode;
            temp->next = head;
            head = temp;
        }
    }
    while(head->next!=NULL){
        if(head->node->val < head->next->node->val ){
            head->next->node->right = head->node;
            answer = head->next->node;

        }else if(head->node->val > head->next->node->val){
            head->node->left = head->next->node;
        }
        head = head->next;
    }
    if (answer == NULL) answer = head->node;
    // printf("%d %d %d", answer->val, answer->left->val, answer->left->left->val);
    return answer;

}

int main(){
    int num[] = {1,2,3};
    int sizeofNum = sizeof(num)/sizeof(num[0]);
    struct TreeNode* returnTree = constructMaximumBinaryTree(num,sizeofNum);
}
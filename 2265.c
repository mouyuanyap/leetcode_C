#include <stdio.h>
#include <stdlib.h>
#include "binarySearchTree.h"


int* postOrderTraverse(struct TreeNode* root, int* count){
    int l=-1,r=-1,num1=0, num2=0;
    int *sum = (int*)malloc(3*sizeof(int));
    *sum = 0;
    *(sum+1) = 0;
    if(root->left!=NULL){
        int *tmp = (int*)malloc(2*sizeof(int));
        tmp = postOrderTraverse(root->left, count);
        l = *tmp;
        num1 = *(tmp+1);
    }   
    
    if(root->right!=NULL){
        int *tmp = (int*)malloc(2*sizeof(int));
        tmp = postOrderTraverse(root->right,count);
        r= *tmp;
        num2 = *(tmp+1);
    } 
    // int sum;
    if (l==-1 && r==-1){
        *sum = root->val;
        
    }else if(l!=-1 && r==-1){
        *sum = root->val + l;
        
    }else if(l==-1 && r!=-1){
        *sum = root->val + r;
        
    }else{
        *sum = root->val + r + l;
    }
    *(sum+1)+= num1;
    *(sum+1)+= num2;
    *(sum+1)+= 1;
    if (root->val == *sum / *(sum+1)) *count+=1;
    *(sum+2) = *count;
    return sum;
    // if (l!=-1)
}

int averageOfSubtree(struct TreeNode* root){
    int* count = (int*)malloc(sizeof(int));
    *count =0;
    int* answer = (int*)malloc(3*sizeof(int));
    answer = postOrderTraverse(root,count);
    return *count;
}

int main(){
    
    int num[] = {4,2,7,1,3};
    int sizeofNum = sizeof(num)/sizeof(num[0]);
    struct TreeNode* root = NULL;
    struct TreeNode* bst = binarySearchTree(root,num,sizeofNum);
    averageOfSubtree(bst);

}
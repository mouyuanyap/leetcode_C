#include <stdio.h>
#include <stdlib.h>
#include "binarySearchTree.h"


void inOrderTransverse(struct TreeNode* root,int val,struct TreeNode* ans){
    if(root->left!=NULL){
        inOrderTransverse(root->left, val,ans);
    } 
    if (root->val == val){
        *ans = *root;
    }else if (root->val < val){
        if(root->right!=NULL) inOrderTransverse(root->right, val,ans);
    }
    
}

struct TreeNode* searchBST(struct TreeNode* root, int val){
    struct TreeNode* ans= (struct TreeNode*)calloc(1, sizeof(struct TreeNode));;

    inOrderTransverse(root,val, ans);
    return ans;
}

int main(){
    int num[] = {4,2,7,1,3};
    int sizeofNum = sizeof(num)/sizeof(num[0]);
    struct TreeNode* root = NULL;
    struct TreeNode* bst = binarySearchTree(root,num,sizeofNum);
    struct TreeNode* ans = NULL;
    ans = searchBST(bst,2);
}
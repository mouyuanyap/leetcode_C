#include <stdio.h>
#include <stdlib.h>
#include "binarySearchTree.h"

int traverseRight(struct TreeNode* root, int *max);

void traverseLeft(struct TreeNode* root, int father, int* max ){
    int a = 0;
    if (root->right!=NULL){
        a = traverseRight(root->right, max);
    }
    if (a > *max){
        root->val+=a;
        if (root->val > *max) *max = root->val;
    } else{
        root->val+=*max;
        if (root->val > *max) *max = root->val;
    }

    if(root->left!=NULL) traverseLeft(root->left, root->val, max);
}

int traverseRight(struct TreeNode* root, int *max){
    if (root->right==NULL){
        root->val+=*max;
        if (root->val > *max) *max = root->val;

        if(root->left!=NULL) traverseLeft(root->left,root->val, max);
        return root->val;
    } 
    else{
        int a = traverseRight(root->right, max);
        if (a > *max){
            root->val+=a;
            if (root->val > *max) *max = root->val;
        } else{
            root->val+=*max;
            if (root->val > *max) *max = root->val;
        }
        if(root->left != NULL) traverseLeft(root->left,root->val, max);
        return root->val;
    }

}

struct TreeNode* bstToGst(struct TreeNode* root){
    int *max = (int*)malloc(sizeof(int));
    *max =  0;
    traverseRight(root, max);
    return root;
}

int main(){
    int array[] = {4,1,6,0,2,5,7,3,8};
    int sizeOfArray = sizeof(array)/sizeof(array[0]);
    struct TreeNode* bst = binarySearchTree(NULL, array, sizeOfArray);
    struct TreeNode* gst = bstToGst(bst);
}
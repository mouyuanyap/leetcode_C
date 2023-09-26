#include <stdio.h>
#include <stdlib.h>

struct TreeNode{
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

void insert(struct TreeNode* root, int num){
    if (num <= root->val){
        if (root->left){
            insert(root->left, num);
        }else{
            struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(TreeNode));
            newNode->val = num;
            newNode->left = NULL;
            newNode->right = NULL;
            root->left = newNode;
        }
    }else{
        if (root->right){
            insert(root->right, num);
        }else{
            struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(TreeNode));
            newNode->val = num;
            newNode->left = NULL;
            newNode->right = NULL;
            root->right =newNode;
        }
    }
}

struct TreeNode* binarySearchTree(struct TreeNode* root, int* array, int sizeOfArray){
    int index = 0;
    
    if (!root){
        root = (struct TreeNode*)malloc(sizeof(TreeNode));
        root->val = array[index];
        root->left = NULL;
        root->right = NULL;
        index++;
    } 
    for (int i = index; i<sizeOfArray; i++){
        insert(root, array[i]);
    }
    return root;

}

void inOrderTransversal(struct TreeNode* node){
    if (node->left) inOrderTransversal(node->left);
    printf("%d, ", node->val);
    if (node->right) inOrderTransversal(node->right);
}


// int main(){
//     struct TreeNode* root = NULL;
//     int num[] = {2,6,2,1,5,7,8,3};
//     int sizeofNum = sizeof(num)/sizeof(num[0]);
//     struct TreeNode* bst = binarySearchTree(root, num, sizeofNum);
//     int num2[] = {4,0,9};
//     int sizeofNum2 = sizeof(num2)/sizeof(num2[0]);
//     struct TreeNode* bst2 = binarySearchTree(bst, num2, sizeofNum2);
//     inOrderTransversal(bst2);

// }

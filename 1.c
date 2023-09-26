#include <stdio.h>
#include <stdlib.h>
#include "mergeSortArray.h"

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int *sortedArray = (int*)calloc(numsSize,sizeof(int));
    sortedArray = mergeSortArray(nums,numsSize);

    returnSize[0] = 2;
    int* returnValue = (int*)calloc(2,sizeof(int));
    returnValue[0] = -1;
    returnValue[1] = -1;

    
    for (int i=0; i<numsSize-1; i++){
        for(int j=i+1; j<numsSize; j++){
            if (target - nums[i] == nums[j]){
                returnValue[0] = i;
                returnValue[1] = j;
                break;
            }else if (target - nums[i] < nums[j]){
                break;
            }
        }
        if (returnValue[0]!=-1) break;
    }
    return returnValue;
}

char* maximumOddBinaryNumber(char* s){
    int i = 0;
    int numOne = 0;
    while(s[i] != '\0'){
        i++;
        if (s[i] == '1') numOne++;
    }
    int numZero = i - numOne;
    for (int j = 0; j< numOne - 1; j ++){
        s[j] = '1';
    }
    for (int j = numOne - 1; j< numZero + numOne - 1; j ++){
        s[j] = '0';
    }
    s[i-1] = '1';
    return s;
}

int main(){
    int nums[] = {0,4,3,0};
    int numsSize = sizeof(nums)/sizeof(nums[0]);
    int target = 0;
    int returnSize[] = {2};
    twoSum(nums,numsSize,target,returnSize);
    maximumOddBinaryNumber("1");
}
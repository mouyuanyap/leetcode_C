#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int* nums, int numsSize, int target, int* returnSize){
    returnSize[0] = 2;
    int* result = (int*)calloc(2,sizeof(int));
    result[0] = -1;
    result[1] = -1;
    int start = 0;
    int end = numsSize;
    
    while (start!=end){
        int mid = (start + end)/2;
        if (nums[mid] == target){
            result[0] = mid;
            break;
        }
        else if(nums[mid] < target){
            start = mid + 1;
        }
        else if(nums[mid] > target){
            end = mid;
        }   
    }

    if (result[0] != -1){
        for (int i = result[0]+1; i < numsSize; i++){
            if (nums[i]!=target){
                break;
            }else{
                result[1] = i;
            }
        }
    }

    for (int i = result[0]-1; i >= 0; i--){
        if (nums[i]!=target){
            break;
        }else{
            if (result[1]==-1){
                result[1] = result[0];
                result[0] = i;
            }else{
                result[0] = i;
            }
            
        }
    }

    // if (result[1]<result[0]){
    //     int temp;
    //     temp = result[0];
    //     result[0] = result[1];
    //     result[1] = temp;
    // }



    return result;

}

int main(){
    // int nums[] = {5,7,7,8,8,10};
    // int target = 8;
    int nums[] = {2,2};
    int target = 2;
    int size = sizeof(nums)/sizeof(nums[0]);
    int returnSize[] = {-1};

    int *result = searchRange(nums, size, target, returnSize);
    printf("%d,%d", result[0],result[1]);
    return 0;
}
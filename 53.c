#include <stdio.h>
#include <stdlib.h>

int maxSubArray(int* nums, int numsSize){
    int *dp = (int*)calloc(numsSize, sizeof(int));
    int max = nums[0];
    dp[0] = nums[0];
    for(int i = 1; i<numsSize; i++){
        if (dp[i-1]+nums[i] > dp[i-1] && dp[i-1]+nums[i] > nums[i]){
            dp[i] = dp[i-1]+nums[i];
        }else if (dp[i-1]+nums[i] > nums[i]){
            dp[i] = dp[i-1]+nums[i];
        }else{
            dp[i] = nums[i];
        }
        if (dp[i]> max) {
            max = dp[i];
        }
    }
    return max;
}

int main(){
    int nums[] = {5,4,-1,7,8};
    int size = sizeof(nums)/sizeof(nums[0]);
    maxSubArray(nums,size);
}
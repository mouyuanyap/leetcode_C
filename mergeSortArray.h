#include <stdio.h>
#include <stdlib.h>

int* mergeArray(int *num1, int* num2, int num1Size, int num2Size){  
    int i=0, j=0;
    int* ans = (int*)calloc(num1Size+num2Size, sizeof(int));
    while (i<num1Size && j <num2Size){
        if (num1[i]<=num2[j]){
            ans[i+j] = num1[i];
            i++;
        }else{
            ans[i+j] = num2[j];
            j++;
        }
    }
    while (i<num1Size){
        ans[i+j] = num1[i];
        i++;
    }
    while (j<num2Size){
        ans[i+j] = num2[j];
        j++;
    }
        
    return ans;
}

int* mergeSortArray(int *num1, int size){
    int mid = size/2;
    if (mid == 0){
        return num1;
    }
    int* left = (int*)calloc(mid, sizeof(int));
    int* right = (int*)calloc(size - mid, sizeof(int));
    for (int i = 0; i<mid; i++){
        left[i] = num1[i];
    }
    for (int i = mid; i < size; i++){
        right[i-mid] = num1[i];
    }
    int* sortedLeft = mergeSortArray(left, mid);
    int* sortedRight = mergeSortArray(right, size-mid);
    return mergeArray(sortedLeft,sortedRight, mid, size-mid);

}


// int main(){
//     int num[] = {2,1,5,4,6};
//     int size = sizeof(num)/sizeof(num[0]);
//     int* sorted = mergeSortArray(num,size);

// }
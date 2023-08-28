#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int returnHashKey(int num){
    int key;
    if (num>=0){
        key = num;
        return key;
    }else{
        printf("%d,%d\n",num,key);
        key = 1000 + (-num) -1;
        return key;
    }
}

bool uniqueOccurrences(int* arr, int arrSize){
    int *countHashMap = (int*)calloc(2001,sizeof(int));
    int *occurrenceHashMap = (int*)calloc(1000,sizeof(int));
    for (int i = 0; i < arrSize; i++){
        countHashMap[returnHashKey(arr[i])] +=1;
        occurrenceHashMap[countHashMap[returnHashKey(arr[i])]-1] -=1;
        occurrenceHashMap[countHashMap[returnHashKey(arr[i])]] +=1;
    }
    for (int i = 0; i < 1000; i++){
        if (occurrenceHashMap[i] > 1){
            return false;
        }
    }
    return true;
}

int main(){
    int num[] = {-3,0,1,-3,1,1,1,-3,10,0,10};
    if (uniqueOccurrences(num, sizeof(num)/sizeof(num[0]))){
        printf("ok");
    }else{printf("no");}
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int maxConsecutiveAnswers(char * answerKey, int k){
    int i = 0;
    while(answerKey[i]!='\0'){
        i++;
    }
    int *prefT = (int *)calloc(i, sizeof(int));
    int *prefF = (int *)calloc(i, sizeof(int));
    i = 0;
    while(answerKey[i]!='\0'){
        if (i==0){
            prefF[i] = (int)(answerKey[i] == 'F');
            prefT[i] = (int)(answerKey[i] == 'T');

        }else{
            prefT[i] = prefT[i-1]+ (int)(answerKey[i] == 'T');
            prefF[i] = prefF[i-1]+ (int)(answerKey[i] == 'F');
        }
        i++;    
    }
    if (i == 1) return 1;
    int max = INT32_MIN;
    int left = -1;
    for (int a = 0; a<i; a ++){
        printf("%d \t %d\n", prefT[a],prefF[a]);
        int x,y;
        if (left == -1){x = 0; y = 0;}
        else{x = prefT[left]; y = prefF[left];}
        while (prefT[a] - x >k){
            left+=1;
            x = prefT[left];
            y = prefF[left];
        }
        if (prefF[a]-y+ prefT[a] - x>max) max = prefF[a]-y + prefT[a] - x;
    }

    left = -1;
    for (int a = 0; a<i; a ++){
        // printf("%d \t %d\n", prefT[a],prefF[a]);
        int x,y;
        if (left == -1){x = 0; y = 0;}
        else{x = prefF[left]; y = prefT[left];}
        while (prefF[a] - x >k){
            left+=1;
            x = prefF[left];
            y = prefT[left];
        }
        if (prefT[a]-y+ prefF[a] - x>max) max = prefT[a]-y + prefF[a] - x;
    }

    printf("%d", max);
    return max;
    // int left = 0, right = 0;
    // int* change = (int*)calloc(k,sizeof(k));
    
}

int main(){
    maxConsecutiveAnswers("TF", 1);
    return 0;
}
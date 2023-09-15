#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int returnLen(char *a){
    int i = 0;
    while (a[i]!='\0'){
        i++;
    }
    return i;
}

char * addBinary(char * a, char * b){
    int lenA, lenB;
    lenA = returnLen(a);
    
    lenB = returnLen(b);
    char zeroOne[] = {'0','1'};

    char *ans;
    int sizeOfAns;
    if (lenA>lenB){
        ans = (char*)calloc(lenA+1,sizeof(char));
        sizeOfAns = lenA+1;
    }else{
        ans = (char*)calloc(lenB+1,sizeof(char));
        sizeOfAns = lenB+1;
    }
    char carry = '0';
    int i = 0;
    ans[sizeOfAns - 1] = '\0';
    while(lenA-i-1>-1 && lenB-i-1>-1){
        ans[sizeOfAns-i-2] = zeroOne[a[lenA-i-1]&1 ^ b[lenB-i-1]&1 ^ carry&1];
        carry = ((a[lenA-i-1]&1) & (b[lenB-i-1]&1) || (((a[lenA-i-1]&1) | (b[lenB-i-1]&1)) & carry&1)) ? '1' : '0';
        i++;
    }
    while(sizeOfAns-i-2 > -1){
        if (lenA == sizeOfAns-1){
            ans[sizeOfAns-i-2] = zeroOne[a[lenA-i-1]&1 ^ carry&1];
            carry = (a[lenA-i-1]&1) & (carry&1) ? '1' : '0';
        }
        else{
            ans[sizeOfAns-i-2] = zeroOne[b[lenB-i-1]&1 ^ carry&1];
            carry = (b[lenB-i-1]&1) & (carry&1) ? '1' : '0';
        }
        i++;
    }
    if (carry == '1'){
        char *newAns;
        newAns = (char*)calloc(sizeOfAns+1,sizeof(char));
        newAns[0] = '1';
        for (int j = 1; j<sizeOfAns+1; j++){
            newAns[j] = ans[j-1];
        }
        newAns[sizeOfAns] = '\0';
        // free(ans);
        return newAns;
    }else{
        return ans;
    }
    return a;
}

int main(){
    char a[] = "1";
    char b[] = "0";
    char* c = addBinary(a,b);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
bool checkOverflow(int x, long y){
    // printf("%d\n", x>>31);
    // printf("%d\n", y>>31);
    if (y> pow(2,31)-1 && y<-(pow(2,31)) ){
        return true;
    }
    if ((x>>31)^(y>>31)){
        return true;
    }else{return false;}
}
int reverse(int x){
    int ori = x;
    long answer = 0;
    
    while (x!=0){
        answer = answer*10 + x%10;
        x = x/10; 
    }
    if (checkOverflow(ori,answer)){
        return 0;
    }else{
        return answer;
    }
}

int main(){
    int a = 1534236469;
    printf("%d", reverse(a));
}
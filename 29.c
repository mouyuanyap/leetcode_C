#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int divide(int dividend, int divisor){
    int sign = (dividend>>31) ^ (divisor>>31);
    if (dividend>>31 == -1 && dividend != -pow(2,31)) dividend = -dividend;
    if (divisor>>31 == -1 && divisor != -pow(2,31)) divisor = -divisor;
    // dividend = -dividend-1;
    // divisor = -divisor;
    long ans = 0;
    long div = dividend;
    if (dividend == -pow(2,31)){
        if (sign == 0 && divisor == 1){
            ans = pow(2,31) - 1;
            return ans;
        }else{
            div = pow(2,31);
        }
        
    } 

    if (divisor == -pow(2,31) && dividend == -pow(2,31)){
        return 1;
    }else if(divisor == -pow(2,31)) {
        return 0;
    }
   
    while (div > 0){
        int i = 0;
        while (i<31 && ((uint32_t)divisor<<(i+1))>>31 != 1 && (uint32_t)divisor<<i <= div){
            i++;
        }
        if (i-1<0){
            i = 1;
            if (ans == 0 && divisor <= div) ans = 1;
            div -= (uint32_t)divisor << (i-1);
            
        
        }else{
            div -= (uint32_t)divisor << (i-1);
            ans += 1 << (i-1); 
        } 
        
        
    }


    if (sign == -1){ans = -ans;}
    int a = (int)ans;
    return ans;
    
    
}


int main(){
    int a = -2147483648;
    // int a = 50;
    int b = -1109186033;
    int c = divide(a,b);
}


// inline uint32_t uabs(int i)
// {
//     return i < 0 ? ~(uint32_t) i + 1 : i;
// }

// int divide(int dividend, int divisor) {
//     // Get rid of signs because bitwise math is easier with positive numbers
//     uint32_t remainder = uabs(dividend);
//     uint32_t positiveDivisor = uabs(divisor);
    
//     // Long division algorithm everyone learned in grade school, except in binary instead of decimal
//     uint32_t result = 0;
//     for (int i = 31; i >= 0; --i) {
//         uint32_t curDividend = remainder >> i;
//         if (curDividend >= positiveDivisor) {
//             result += 1u << i;
//             remainder -= positiveDivisor << i;
//         }
//     }
    
//     // Reintroduce the sign as appropriate
//     if ((dividend > 0 && divisor > 0) || (dividend < 0 && divisor < 0)) {
//         return result >= (uint32_t) INT_MAX ? INT_MAX : (int) result;
//     }
//     else {
//         // Invert bits and add one instead of multiplying by -1
//         return result > (uint32_t) INT_MAX ? INT_MIN : ((int) ~result) + 1;
//     }
// }
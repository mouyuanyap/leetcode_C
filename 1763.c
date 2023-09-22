#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
char * longestNiceSubstring(char * s){
    int i=0,j=0;
    int num=0;
    int lenLeft = 0, lenRight = 0;
    
    int *hashMap = (int*)calloc(26,sizeof(int));
    while(s[num]!='\0'){
        if (s[num] >= (int)'a' &&s[num] <= (int)'z'){
            if(hashMap[(int)(s[num]^32)%26] == -1){
                hashMap[(int)(s[num]^32)%26] = 2;
            }else if (hashMap[(int)(s[num]^32)%26] != 2){
                hashMap[(int)(s[num]^32)%26] = 1;
            }
            
        }else{
            
            if(hashMap[(int)(s[num])%26] == 1){
                hashMap[(int)(s[num])%26] = 2;
            }else if (hashMap[(int)(s[num])%26] != 2){
                hashMap[(int)(s[num])%26] = -1;
            }
        }
        num+=1;
    }
    
    for (int x=0;x<num;x++){
        int y;
        if (s[x] >= (int)'a' &&s[x] <= (int)'z'){
            y = (int)(s[x]^32)%26;
            
        }else{
            y = (int)(s[x])%26;
        }
        printf("%d\n",y);
        if (hashMap[y]<2){
            lenLeft = x;
            lenRight = num-x-1;
            
            char* stringLeft = (char*)calloc(lenLeft+1,sizeof(char));
            char* stringRight = (char*)calloc(lenRight+1,sizeof(char));
            for (int c = 0; c < x; c++){
                stringLeft[c] = s[c];
                
            }
            stringLeft[x] = '\0';
    
            for (int c = x+1; c < num; c++){
                stringRight[c-(x+1)] = s[c];

            }
            
            stringRight[lenRight] = '\0';
            
            char *leftNice = longestNiceSubstring(stringLeft);
            char *rightNice = longestNiceSubstring(stringRight);

            if (strlen(leftNice)>= strlen(rightNice)){
                return leftNice;
            }else{
                return rightNice;
            }


            break;
        }
    }
    return s;

}
// char * longestNiceSubstring(char * s){
//     int i = 0;
//     int left = 0;
//     char a = '-';
//     int ansL = 0, ansR = 0;
//     int ansLength = -1;
//     int good = 1;
//     while(s[i]!='\0' && a!='\0'){
//         if (a == '-') {
//             a = s[i];
//             i++;
//             continue;
//         }

//         if ((char)(s[i]^32) == a || (char)(s[i]^32^32) == a){
//             if (i+1-left>ansLength){
//                 i+=1;
//                 ansL = left;
//                 ansR = i;
//                 ansLength = ansR-ansL;
//                 good = 1;
//             }else{
//                 left = i;
//                 i+=1;
                
//                 a = s[left];
//             }

            

//         }else{
//             if (good == 1){
//                 a=s[i];
//                 i+=1;
//                 good = 0;
//             }else{
//                 left = i;
//                 i+=1;
            
//                 a = s[left];
//             }
            
//         }
//     }
//     char* ans = (char*)calloc(ansR-ansL+1, sizeof(char));
//     int j = 0;
//     for (int i = ansL; i < ansR; i++){
//         ans[j] = s[i];
//         j++;
//      }
//      ans[j] = '\0';
//      return ans;
// }

int main(){
    char *a = longestNiceSubstring("YazaAay");
}
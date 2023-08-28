#include <stdio.h>
#include <stdlib.h>

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n){
    if (m!=1){
        int j = 0;
        int k = 0;
        if (n!=0){
            for (int i = 0; i < m; i++){
                if(j<n && nums1[i]>nums2[j]){
                    nums1[m+j] = nums1[i];
                    nums1[i] = nums2[j];
                    j++;
                }
                int flag = 0;
                for (int a = k-1; a<j; a++){
                    if((nums1[i]>nums1[m+a])) {
                        int temp = nums1[i+flag];
                        nums1[i+flag] = nums1[m+a];
                        nums1[m+a] = temp;
                        flag += 1;
                    }
                }
                if (flag == 1){
                    k++;
                }
                if ( (j==n && nums1[i]>nums1[m+j-1])){
                    int temp = nums1[i];
                    nums1[i] = nums1[m+j-1];
                    nums1[m+j-1] = temp;
                
                }
            }
            for (int i = j; i<n; i++){
                if (k<=j){
                    int flag = 0;
                    if (k!=j) {
                        for (int a=j-1; a>=k;a--){
                            if (nums1[m+a]>=nums2[i]){
                                nums1[m+i-flag] = nums1[m+a];
                                nums1[m+a] = nums2[i];
                                flag += 1;
                                // break;
                                // j++;
                                // k++;
                            }

                        }
                    }else{
                        for (int a=j-1; a>=k;a--){
                            if (m+a < m && nums1[m+a]>=nums2[i]){
                                nums1[m+i-flag] = nums1[m+a];
                                nums1[m+a] = nums2[i];
                                flag += 1;
                                // break;
                                // j++;
                                // k++;
                            }

                        }
                    }
                    
                    if (flag != 0){
                        j++;
                        k++;
                    }else{
                        nums1[m+i] = nums2[i];
                    }
                    
                }else{
                    nums1[m+i] = nums2[i];
                }
                
            }
        }
        
    }else{
        int y = 0;
        for(int i = 0; i<n; i++){
            if (nums2[i]<nums1[y]){
                nums1[y+1] = nums1[y];
                nums1[y] = nums2[i];
                y+=1;
                
            }else{
                nums1[i+1] = nums2[i];
            }
        }
    }
}

int main(){
    // int nums1[] = {3,0};
    // int nums2[] = {3};
    // merge(nums1, 2, 1, nums2, 1, 1);
    int nums1[] = {0};
    int nums2[] = {1};
    // int nums1[] = {2,3,6,0};
    // int nums2[] = {4};
    merge(nums1, 1, 0, nums2, 1, 1);
    for (int i = 0; i < sizeof(nums1)/sizeof(nums1[0]); i++){
        printf("%d\n", nums1[i]);
    }
}
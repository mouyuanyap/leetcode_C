#include <stdio.h>
#include <stdlib.h>

int maxProfit(int* prices, int pricesSize){
    int ans = 0;
    int min = prices[0], max = prices[0];

    for (int i = 1; i < pricesSize; i++){
        if (prices[i] > min){
            max = prices[i];
            ans += max - min;
            min = prices[i];
        }
        if (prices[i] < min){
            min = prices[i];
            max = prices[i];
        }
    }
    return ans;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h>

struct mapLList{
    int time;
    struct serverRequestLList *serverRequest;
    struct mapLList *next;
}mapLList;


struct serverRequestLList{
    int serverID;
    struct serverRequestLList *next;
}serverRequestLList;

int returnHash(int num){
    int result = num%1000000;
    return result;
}

int* countServers(int n, int** logs, int logsSize, int* logsColSize, int x, int* queries, int queriesSize, int* returnSize){
    returnSize[0] = queriesSize;
    struct mapLList **serverMap = (struct mapLList **)calloc(1000000, sizeof(struct mapLList*));
    int **dp = (int **)calloc(1000000, sizeof(int*));
    for (int i = 0; i<1000000; i++){
        for (int j = 0; j<1000000; j++){
            dp[i][j] = -1;
        }
    }
    printf("%d,%d",logsSize, *logsColSize);
    for (int lSize = 0;lSize<logsSize; lSize++){
        int hashNumber = returnHash(logs[lSize][1]);
        if (serverMap[hashNumber] == NULL){
            serverMap[hashNumber] = (struct mapLList *)calloc(1, sizeof(struct mapLList));
            serverMap[hashNumber]->time = logs[lSize][1];
            serverMap[hashNumber]->next = NULL;
            serverMap[hashNumber]->serverRequest = (struct serverRequestLList*)calloc(1, sizeof(struct serverRequestLList));
            serverMap[hashNumber]->serverRequest->serverID = logs[lSize][0];
            serverMap[hashNumber]->serverRequest->next = NULL; 
        }else{
            struct mapLList *cur = serverMap[hashNumber];
            // struct mapLList *prev = NULL;
            while (cur && cur->time!=logs[lSize][1]){
                cur = cur->next;
            }
            if(cur){
                struct serverRequestLList *tempRequest = (struct serverRequestLList*)calloc(1, sizeof(struct serverRequestLList));
                // struct serverRequestLList *curRequest = cur->serverRequest;
                tempRequest -> serverID = logs[lSize][0];
                tempRequest->next =  cur->serverRequest->next;
                cur->serverRequest->next = tempRequest;
            }else{
                struct mapLList *newServerNode = (struct mapLList *)calloc(1, sizeof(struct mapLList));
                newServerNode->time = logs[lSize][1];
                newServerNode->serverRequest =  (struct serverRequestLList*)calloc(1, sizeof(struct serverRequestLList));
                newServerNode->serverRequest->serverID = logs[lSize][0];
                newServerNode->serverRequest->next = NULL;
                newServerNode->next = serverMap[hashNumber];
                serverMap[hashNumber] = newServerNode;
            }
        }
    }
    
    int* returnValue = (int*)calloc(queriesSize,sizeof(int));
    
    for (int query = 0; query < queriesSize; query++){
        struct serverRequestLList *answer = NULL;
        int ansLength = 0;
        for (int start = queries[query]-x; start < queries[query]+1; start ++){
            struct mapLList *cur = serverMap[returnHash(start)];
            while (cur && cur->time != start){
                cur = cur->next;
            }
            if (cur){
                struct serverRequestLList *curRequest = cur->serverRequest;
                while(curRequest){
                    if(!answer){
                        answer = (struct serverRequestLList*)malloc(sizeof(struct serverRequestLList));
                        answer->serverID = curRequest->serverID;
                        answer->next = NULL;
                        ansLength +=1;
                    }else{
                        struct serverRequestLList *curAnswer = answer;
                        while(curAnswer){
                            if (curAnswer->serverID == curRequest->serverID) break;
                            curAnswer = curAnswer->next;
                        }
                        if (!curAnswer){
                            struct serverRequestLList *newNode = (struct serverRequestLList*)malloc(sizeof(struct serverRequestLList));
                            newNode->serverID = curRequest->serverID;
                            newNode -> next = answer;
                            answer = newNode;
                            ansLength +=1;
                        }
                    }
                    curRequest = curRequest->next;
                }
            }
            dp[queries[query]-x][start] = ansLength;
            if (ansLength == n) {
                
                break;
            }

        }

        returnValue[query] = n - ansLength;
    }
    

    return returnValue;
}

int main(){
    int n = 3;
    int logsSize = 3;
    // int **logs = (int**)calloc(logsSize,sizeof(int*));
    int* logs[] = {(int[]){1,3},(int[]){2,6},(int[]){1,5}};
    int logsColSize[] = {2};
    int x = 5;
    int queries[] = {10,11};
    int returnSize[] = {sizeof(queries)/sizeof(queries[0])};
    int *ans = (int*)calloc(returnSize[0],sizeof(int));

    ans = countServers(n, logs, logsSize, logsColSize, x, queries,sizeof(queries)/sizeof(queries[0]), returnSize);
}

// for (int lSize = 0;lSize<logsSize; lSize++){
        
//         if (serverMap[logs[lSize][0]] == NULL){
//             serverMap[logs[lSize][0]]->server_id = logs[lSize][0];
//             serverMap[logs[lSize][0]]->next = NULL;
//             serverMap[logs[lSize][0]]->serverRequest = (struct serverRequestLList*)calloc(1, sizeof(struct serverRequestLList));
//             serverMap[logs[lSize][0]]->serverRequest->time = logs[lSize][1];
//             serverMap[logs[lSize][0]]->serverRequest->next = NULL; 
//         }else{
//             struct mapLList *cur = serverMap[logs[lSize][0]];
//             // struct mapLList *prev = NULL;
//             while (cur && cur->server_id!=logs[lSize][0]){
//                 cur = cur->next;
//             }
//             if(cur){
//                 struct serverRequestLList *tempRequest = (struct serverRequestLList*)calloc(1, sizeof(struct serverRequestLList));
//                 struct serverRequestLList *curRequest = cur->serverRequest;
//                 tempRequest -> time = logs[lSize][1];
//                 //enter request list in sorted sequence;
//                 while (curRequest){
//                     if (logs[lSize][0] <= curRequest->time && cur->serverRequest == curRequest){
//                         tempRequest->next = curRequest;
//                         serverMap[logs[lSize][0]]->serverRequest = tempRequest;
//                     }
//                     else if (curRequest->next){
//                         if (logs[lSize][1]>= curRequest->time && logs[lSize][0] <= curRequest->next->time){
                            
//                             tempRequest -> next = curRequest->next;
//                             curRequest->next = tempRequest;
//                         }
//                     }else{

//                     }
//                     curRequest = curRequest->next;
//                 }
                
//             }else{
//                 struct mapLList *newServerNode = (struct mapLList *)calloc(1, sizeof(struct mapLList));
//                 newServerNode->server_id = logs[lSize][0];
//                 newServerNode->serverRequest =  (struct serverRequestLList*)calloc(1, sizeof(struct serverRequestLList));
//                 newServerNode->serverRequest->time = logs[lSize][1];
//                 newServerNode->serverRequest->next = NULL;
//                 newServerNode->next = serverMap[logs[lSize][0]];
//                 serverMap[logs[lSize][0]] = newServerNode;
                
//             }
//         }
//     }
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TweetLibrary{
    int PK;
    int tweetID;
    struct TweetLibrary *next;
} TweetLibrary;

typedef struct UserTweetList{
    // int tweetID;
    struct UserTweetList *next;
    TweetLibrary *pointToLibrary;
} UserTweetList;

typedef struct UserLList{
    struct User* user;
    struct UserLList* next;
} UserLList;

typedef struct User{
    int userID;
    UserTweetList *tweetList;
    struct UserLList* following;
    int numFollowing;
    
} User;

typedef struct {
    TweetLibrary *tweetHead;
    int totalTweet;
    User **allUser;
} Twitter;


Twitter* twitterCreate() {
    Twitter* twitter = (Twitter*)malloc(sizeof(Twitter));
    twitter->totalTweet = -1;
    twitter->tweetHead = NULL;
    twitter->allUser = (User**)calloc(500,sizeof(User*));
    return twitter;
}

void twitterFollow(Twitter* obj, int followerId, int followeeId) {
    if (obj->allUser[followeeId - 1] == NULL){
        obj->allUser[followeeId - 1] = (User *)malloc(sizeof(User));
        obj->allUser[followeeId - 1] -> userID = followeeId;
        obj->allUser[followeeId - 1] -> tweetList = NULL;
        obj->allUser[followeeId - 1] -> following = NULL;
        obj->allUser[followeeId - 1] -> numFollowing = 0;
        twitterFollow(obj,followeeId,followeeId);
        

    }

    if (obj->allUser[followerId - 1] == NULL){
        obj->allUser[followerId - 1] = (User *)malloc(sizeof(User));
        obj->allUser[followerId - 1] -> userID = followerId;
        obj->allUser[followerId - 1] -> tweetList = NULL;
        obj->allUser[followerId - 1] -> following = NULL;
        obj->allUser[followerId - 1] -> numFollowing = 0;
        twitterFollow(obj,followerId,followerId);
        // UserLList* temp = (UserLList*)malloc(sizeof(UserLList));
        // temp->user = obj->allUser[followeeId - 1];
        // temp->next = (UserLList*)malloc(sizeof(UserLList));
        // if (!obj->allUser[followerId - 1] -> following) obj->allUser[followerId - 1] -> following = (UserLList*)malloc(sizeof(UserLList)); 
        // temp->next = obj->allUser[followerId - 1] -> following;
        // obj->allUser[followerId - 1] -> following = temp;
        // obj->allUser[followerId - 1] -> following = (UserLList*)malloc(sizeof(UserLList));
        
        // obj->allUser[followerId - 1] -> following -> user = obj->allUser[followeeId - 1];
        // obj->allUser[followerId - 1] -> following -> next = NULL;
    }
    UserLList* temp = (UserLList*)malloc(sizeof(UserLList));
    temp->user = obj->allUser[followeeId - 1];
    temp->next = NULL;
    if (obj->allUser[followerId - 1] -> following == NULL){
        obj->allUser[followerId - 1] -> following = temp;
    }else{
        UserLList* move = obj->allUser[followerId - 1] -> following;
        int exist = 0;
        while (move){
            if (move->user->userID == followeeId){
                exist = 1;
                break;
            }
            move = move -> next;
        }
        if (exist == 0){
            temp->next = obj->allUser[followerId - 1] -> following;
            obj->allUser[followerId - 1] -> following = temp;
        }
        
    }
    
    obj->allUser[followerId - 1] -> numFollowing +=1;
}

void twitterPostTweet(Twitter* obj, int userId, int tweetId) {
    obj->totalTweet +=1;
    if (obj->tweetHead == NULL){
        obj->tweetHead = (TweetLibrary*)malloc(sizeof(TweetLibrary));
        obj->tweetHead->PK = obj->totalTweet;
        obj->tweetHead->next = NULL;
        obj->tweetHead->tweetID = tweetId;
    }else{
        TweetLibrary* temp = (TweetLibrary*)malloc(sizeof(TweetLibrary));
        temp->PK = obj->totalTweet;
        temp->tweetID = tweetId;
        temp->next = obj->tweetHead;
        obj->tweetHead = temp;
    }
    
    if (obj->allUser[userId - 1] == NULL){
        obj->allUser[userId - 1] = (User *)malloc(sizeof(User));
        obj->allUser[userId - 1] -> userID = userId;
        obj->allUser[userId - 1] -> following = NULL;
        obj->allUser[userId - 1] -> numFollowing = 0;
        twitterFollow(obj,userId,userId);
        
        obj->allUser[userId - 1] -> tweetList = (UserTweetList*)malloc(sizeof(UserTweetList));
        // obj->allUser[userId - 1] -> tweetList ->tweetID = tweetId;
        obj->allUser[userId - 1] -> tweetList -> next = NULL;
        obj->allUser[userId - 1] -> tweetList ->pointToLibrary = obj->tweetHead;
    }else{

        if (obj->allUser[userId - 1] -> tweetList == NULL) {
            obj->allUser[userId - 1] -> tweetList = (UserTweetList*)malloc(sizeof(UserTweetList));
            obj->allUser[userId - 1] -> tweetList -> next = NULL;
            obj->allUser[userId - 1] -> tweetList ->pointToLibrary = obj->tweetHead;
        }else{
            UserTweetList* temp = (UserTweetList*)malloc(sizeof(UserTweetList));
            // temp ->tweetID = tweetId;
            temp->next = obj ->allUser[userId - 1] -> tweetList;
            temp->pointToLibrary = obj->tweetHead;
            obj ->allUser[userId - 1] -> tweetList = temp;
        }
    }
}

int* twitterGetNewsFeed(Twitter* obj, int userId, int* retSize) {
    
    int *returnValue = (int*)calloc(10,sizeof(int));
    retSize[0] = 0;

    if (obj->allUser[userId - 1] == NULL){
        retSize[0] = 0;
        int *finalAnswer = NULL;
        return finalAnswer;
    }
    UserTweetList** followeeTweetList = (UserTweetList**)calloc(obj->allUser[userId -1]->numFollowing, sizeof(UserTweetList*));
    UserLList* temp2 = obj->allUser[userId-1]->following;
    int num = 0;
    while (temp2){
        UserTweetList* followeeTweetListTemp = temp2->user->tweetList;
        followeeTweetList[num] = followeeTweetListTemp;
        temp2 = temp2->next;
        num++;
    }
    int max;
    int minID;
    for(int i = 0; i < 10; i++){
        max = -1;
        minID = -1;
        int temp;
        for (int j = 0; j < obj->allUser[userId -1]->numFollowing; j++){
            if (followeeTweetList[j]!= NULL && followeeTweetList[j]->pointToLibrary->PK  > max){
                max = followeeTweetList[j]->pointToLibrary->PK;
                minID = followeeTweetList[j]->pointToLibrary->tweetID;
                temp = j;
            }
        }
        if (minID!=-1){
            if (followeeTweetList[temp]->next != NULL) followeeTweetList[temp] = followeeTweetList[temp]->next;
            else followeeTweetList[temp] = NULL;
            returnValue[i] = minID;
        }else{
            retSize[0] = i;
            break;
        }
    }
    int *finalAnswer = (int*)calloc(retSize[0],sizeof(int));
    for (int i = 0; i<retSize[0]; i++){
        finalAnswer[i] = returnValue[i];
    }
    return finalAnswer;
}



void twitterUnfollow(Twitter* obj, int followerId, int followeeId) {
    UserLList* move = obj->allUser[followerId-1]->following;
    UserLList* prev = NULL;
    while (move->user){
        if (move->user->userID == followeeId){
            if (prev){
                prev->next = move->next;
            }else{
                obj->allUser[followerId-1]->following = move->next;
            }
            obj->allUser[followerId-1]->numFollowing-=1;
            break;
        }
        prev = move;
        move = move->next;
    }

}

void twitterFree(Twitter* obj) {
    free(obj);
}

int main(){
    int* num = (int*)malloc(sizeof(int));
    *num = 10;
    Twitter* obj = twitterCreate();
    // twitterFollow(obj, 1, 2);
    // twitterFollow(obj, 2, 3);
    // twitterFollow(obj, 3, 1);
    // twitterFollow(obj, 1, 3);
    // twitterUnfollow(obj,1,2);
    
    twitterPostTweet(obj, 1, 5);
    twitterPostTweet(obj, 1, 6);
    // twitterPostTweet(obj, 3, 7);
    int* param_2 = twitterGetNewsFeed(obj, 1, num);
    // twitterUnfollow(obj,1,3);
    // param_2 = twitterGetNewsFeed(obj, 1, num);
    // int* param_2 = twitterGetNewsFeed(obj, 1, num);
    // twitterFollow(obj, 1, 2);
    // twitterPostTweet(obj, 2, 6);
    // param_2 = twitterGetNewsFeed(obj, 1, num);
    // twitterUnfollow(obj, 1, 2);
    // param_2 = twitterGetNewsFeed(obj, 1, num);
    // twitterFree(obj);
}
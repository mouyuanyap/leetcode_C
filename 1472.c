#include <stdio.h>
#include <stdlib.h>

typedef struct BrowserHistory{
    char* webpageName;
    struct BrowserHistory* next;
    struct BrowserHistory* prev;
} BrowserHistory;


BrowserHistory* browserHistoryCreate(char * homepage) {
    BrowserHistory *bh;
    bh = (BrowserHistory*)calloc(1,sizeof(BrowserHistory));
    bh->webpageName = (char*)calloc(sizeof(homepage)/sizeof(char),sizeof(char));
    bh->webpageName = homepage;
    bh->next = NULL;
    bh->prev = NULL;
    return bh;
}

void browserHistoryVisit(BrowserHistory* obj, char * url) {
    BrowserHistory* temp;
    temp = (BrowserHistory*)calloc(1,sizeof(BrowserHistory));
    temp->webpageName = (char*)calloc(sizeof(url)/sizeof(char),sizeof(char));
    temp->webpageName =url;
    
    temp->next = NULL;
    temp->prev = (BrowserHistory*)calloc(1,sizeof(BrowserHistory));
    
    *(temp->prev) = *obj;
    // obj->next = (BrowserHistory*)calloc(1,sizeof(BrowserHistory));
    // *(obj->next) = *temp;
    temp->prev->next = (BrowserHistory*)calloc(1,sizeof(BrowserHistory));
    *(temp->prev->next) = *temp;

    // if (obj->prev!=NULL){
    //     obj->prev->next = (BrowserHistory*)calloc(1,sizeof(BrowserHistory));
    //     *(obj->prev->next) = *(temp->prev);
    // }

    *obj = *temp;

}

char * browserHistoryBack(BrowserHistory* obj, int steps) {
    // BrowserHistory* temp;
    // temp = (BrowserHistory*)calloc(1,sizeof(BrowserHistory));
    for (int i = 0; i<steps; i++){
        // *temp = *obj;
        if (obj->prev == NULL){
            break;
        }
        else{
            if (obj->prev->prev != NULL){
                *(obj->prev->prev->next) = *(obj->prev);
            }
            *obj = *(obj->prev);
        }
    }
    
    return obj->webpageName;
}

char * browserHistoryForward(BrowserHistory* obj, int steps) {
    // BrowserHistory* temp;
    for (int i = 0; i<steps; i++){
        // *temp = *obj;
        if (obj->next == NULL){
            break;
        }else{
            *obj = *(obj->next);
        }
    }
    return obj->webpageName;
}

void browserHistoryFree(BrowserHistory* obj) {
    obj->next = NULL;
    obj->prev = NULL;
    obj->webpageName = "";
}

void printCurrentPage(BrowserHistory* obj){
    printf("\ncurrent: %s\n", obj->webpageName);
    if  (obj->prev!=NULL){
        printf("prev: %s\n", obj->prev->webpageName);    
    }
    if(obj->next!=NULL){
        printf("next: %s\n", obj->next->webpageName);
    }
    
}


int main(){
    BrowserHistory *b = (BrowserHistory*)calloc(1,sizeof(BrowserHistory));
    b = browserHistoryCreate("momn.com");
    printCurrentPage(b);
    browserHistoryVisit(b,"bx.com");
    printCurrentPage(b);
    browserHistoryVisit(b,"bjyfmln.com");
    printCurrentPage(b);
    browserHistoryVisit(b,"pwrrbnw.com");
    printCurrentPage(b);
    browserHistoryVisit(b,"mosohif.com");
    printCurrentPage(b);
    browserHistoryBack(b,6);
    printCurrentPage(b);
    // browserHistoryBack(b,7);
    // printCurrentPage(b);
    // browserHistoryForward(b,5);
    // printCurrentPage(b);
    // browserHistoryForward(b,1);
    // printCurrentPage(b);
    
    // browserHistoryBack(b,10);
    // printCurrentPage(b);
    browserHistoryForward(b,5);
    printCurrentPage(b);



}
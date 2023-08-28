#include <stdio.h>
#include <stdlib.h>

typedef struct CacheLList{
    int key;
    int value;
    struct CacheLList *next;
    struct CacheLList *prev;

} CacheLList;

typedef struct CacheAddressLList{
    int key;
    struct CacheLList *cache;
    struct CacheAddressLList *next;
    struct CacheAddressLList *prev;
} CacheAddressLList;

typedef struct CacheTable{
    struct CacheAddressLList *cacheAdd;
} CacheTable;

typedef struct LRUCache{
    struct CacheTable *ct; 

    struct CacheLList *head;
    struct CacheLList *tail;
    int currentSize;
    int capacity;
} LRUCache;


int returnHash(int key, int capacity){
    return key%capacity;
}

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache *cache = (LRUCache*)calloc(1,sizeof(LRUCache));
    cache->ct = (CacheTable*)calloc(capacity,sizeof(CacheTable));
    cache->currentSize = 0;
    cache->capacity = capacity;
    cache->head = (CacheLList*)calloc(1,sizeof(CacheLList));
    cache->tail = (CacheLList*)calloc(1,sizeof(CacheLList));
    cache->head->value = -1;
    cache->tail->value = -1;
    cache->head->next = cache->tail;
    cache->head->prev = NULL;
    cache->tail->next = NULL;
    cache->tail->prev = cache->head;

    return cache;
}

void pushCache(LRUCache* obj,CacheAddressLList* caL,int value,int key){
    caL->cache->next = (CacheLList*)calloc(1,sizeof(CacheLList));
    caL->cache->value = value;
    caL->cache->key = key;
    if (obj->head->value != -1){
        caL->cache->next = obj->head;    
    }else{
        caL->cache->next = obj->tail;
    }
    // *(caL->cache->next) = *(obj->head);
    caL->cache->prev = NULL;
    if (obj->head->prev == NULL){
        obj->head->prev = (CacheLList*)calloc(1,sizeof(CacheLList));
    }
    obj->head->prev = caL->cache;
    obj->head = caL->cache;
}

void popCache(LRUCache* obj,CacheAddressLList* caL){
    caL->cache->prev->next = caL->cache->next;
    caL->cache->next->prev = caL->cache->prev;
}

void popHashTable(CacheAddressLList* obj){
    *obj = *(obj->next);
    // CacheAddressLList* temp = obj;
    // while(temp!=NULL){
    //     if (temp->key == key){

    //     }
    // }
    
}

void popCacheFull(LRUCache* obj){
    int key = obj->tail->prev->key;
    popHashTable(obj->ct[returnHash(key,obj->capacity)].cacheAdd);
    if (obj->tail->prev->prev!=NULL){
        obj->tail->prev->prev->next = obj->tail;
        obj->tail->prev = obj->tail->prev->prev;
        
    }else{
        obj->tail->prev = obj->head;
        obj->head->next = obj->tail;
    }
    obj->currentSize -=1;
    
    
}



void lRUCachePut(LRUCache* obj, int key, int value) {
    

    int cap = obj->capacity;

    if (obj->ct[returnHash(key,cap)].cacheAdd == NULL){
        obj->ct[returnHash(key,cap)].cacheAdd = (CacheAddressLList*)calloc(1, sizeof(CacheAddressLList));
        obj->ct[returnHash(key,cap)].cacheAdd->key = key;
        obj->ct[returnHash(key,cap)].cacheAdd->next = NULL;
        obj->ct[returnHash(key,cap)].cacheAdd->prev = NULL;
        obj->ct[returnHash(key,cap)].cacheAdd->cache = (CacheLList*)calloc(1,sizeof(CacheLList));

        if (obj->head->value == -1){
            // obj->head->value = value;
            // *(obj->ct[returnHash(key,cap)].cacheAdd->cache) = *(obj->head);
            if (obj->currentSize >= cap) popCacheFull(obj);
            pushCache(obj,obj->ct[returnHash(key,cap)].cacheAdd,value,key);
            obj->tail->prev = obj->ct[returnHash(key,cap)].cacheAdd->cache;
            
        }else{
            if (obj->currentSize >= cap) popCacheFull(obj);
            pushCache(obj,obj->ct[returnHash(key,cap)].cacheAdd,value,key);
            // obj->ct[returnHash(key,cap)].c->prev = (CacheLList*)calloc(1,sizeof(CacheLList));
            
        }   
    }else{
        int i = 0;
        int flag = 0;
        CacheAddressLList *tempCA = obj->ct[returnHash(key,cap)].cacheAdd;

        while(tempCA->next!=NULL){
            if (tempCA->key == key){
                flag = 1;
                break;
            }
            i+=1;
            tempCA= tempCA->next;
        }
        if (flag == 1){
            tempCA->cache->value = value;
            popCache(obj,tempCA);
            pushCache(obj,tempCA,value,key);

        }else{ 
            tempCA->next = (CacheAddressLList*)calloc(1, sizeof(CacheAddressLList));
            
            tempCA->next->key = key;
            tempCA->next->next = NULL;
            tempCA->next->cache = (CacheLList*)calloc(1,sizeof(CacheLList));
            if (obj->currentSize >= cap) popCacheFull(obj);
            pushCache(obj,tempCA->next,value,key);
        }

        }
    obj->currentSize +=1;
}


int lRUCacheGet(LRUCache* obj, int key) {

    CacheAddressLList *tempCA = obj->ct[returnHash(key,obj->capacity)].cacheAdd;
    int flag = 0;
    while(tempCA->next!=NULL){
        if (tempCA->key == key){
            flag = 1;
            break;
        }
        tempCA= tempCA->next;
    }
    if (flag == 1){
        popCache(obj,tempCA);
        pushCache(obj,tempCA,tempCA->cache->value,key);
        int result = tempCA->cache->value;
        return(result);
        

    }else{ 
        return -1;
    }

}

void lRUCacheFree(LRUCache* obj) {
    free(obj);
}

void printResult(int i){
    printf('%d\n',i);
}

int main(){
    int a;
    LRUCache *l1 = lRUCacheCreate(10);
    lRUCachePut(l1,1,1);
    lRUCachePut(l1,2,3);
    lRUCachePut(l1,11,2);
    lRUCachePut(l1,1,4);
    // a = lRUCacheGet(l1,1);
    // printResult(a);
    // a = lRUCacheGet(l1,11);
    // printResult(a);
    // a = lRUCacheGet(l1,2);
    // printResult(a);

    
    // a = lRUCacheGet(l1,1);
    // printResult(a);
    // a = lRUCacheGet(l1,11);
    // printResult(a);
    // a = lRUCacheGet(l1,2);
    // printResult(a);

   
    
    // a = lRUCacheGet(l1,1);
    // printResult(a);
    // a = lRUCacheGet(l1,11);
    // printResult(a);
    // a = lRUCacheGet(l1,2);
    // printResult(a);

    
    
    
}
/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 
 * lRUCachePut(obj, key, value);
 
 * lRUCacheFree(obj);
*/
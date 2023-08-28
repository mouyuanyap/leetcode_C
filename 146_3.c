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
    cache->head->key = -1;
    cache->tail->key = -1;
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
    if (obj->head->value == -1){
        obj->tail->prev = caL->cache;
    }else{
        obj->head->prev = caL->cache;
    }
    
    obj->head = caL->cache;
}

void popCache(LRUCache* obj,CacheAddressLList* caL){
    if (caL->cache->prev !=NULL){
        caL->cache->prev->next = caL->cache->next;
        caL->cache->next->prev = caL->cache->prev;
        pushCache(obj,caL,caL->cache->value,caL->key);
    }
    obj->currentSize-=1;
}
CacheAddressLList* popHashTable(CacheAddressLList* obj,int key){
    CacheAddressLList* temp = obj;
    // CacheAddressLList* first = obj;
    while (temp!=NULL){
        if (temp->key == key){
            if (temp->next!=NULL){
                if (temp->prev!=NULL){
                    temp->next->prev = temp->prev;
                    temp->prev->next = temp->next;
                }else{
                    temp = temp->next;
                }
                
            }else{
                if (temp->prev!=NULL){
                    temp->prev->next = NULL;
                }else{
                    temp = NULL;
                }
                
            }
            
            break;
        }
        temp = temp->next;
    }

    while (temp->prev!=NULL){
        temp = temp->prev;
    }
    return temp;
    
    // CacheAddressLList* temp = obj;
    // while(temp!=NULL){
    //     if (temp->key == key){

    //     }
    // }
    
}
void popCacheFull(LRUCache* obj){
    int key = obj->tail->prev->key;
    obj->ct[returnHash(key,obj->capacity)].cacheAdd = popHashTable(obj->ct[returnHash(key,obj->capacity)].cacheAdd,key);
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
    // if (obj->currentSize >= cap){
        
    //     popCacheFull(obj);
    // }

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
            // obj->tail->prev = obj->head;
            // obj->head->next = obj->tail;
            
        }else{
            if (obj->currentSize >= cap) popCacheFull(obj);
            pushCache(obj,obj->ct[returnHash(key,cap)].cacheAdd,value,key);
            // obj->ct[returnHash(key,cap)].c->prev = (CacheLList*)calloc(1,sizeof(CacheLList));
            
        }   
    }
    else{
        // int i = 0;
        int flag = 0;
        CacheAddressLList *tempCA = obj->ct[returnHash(key,cap)].cacheAdd;

        while(tempCA!=NULL){
            if (tempCA->key == key){
                flag = 1;
                break;
            }
            // i+=1;
            if (tempCA->next == NULL){
                break;
            }
            tempCA= tempCA->next;

        }
        if (flag == 1){
            tempCA->cache->value = value;
            popCache(obj,tempCA);
        }else{ 
            
            tempCA->next  = (CacheAddressLList*)calloc(1, sizeof(CacheAddressLList));;
            tempCA->next ->key = key;
            tempCA->next ->cache = (CacheLList*)calloc(1,sizeof(CacheLList));
            tempCA->next->prev = tempCA;
            if (obj->currentSize >= cap) popCacheFull(obj);
            pushCache(obj,tempCA->next ,value,key);
        }

    }
    obj->currentSize +=1;
}

int lRUCacheGet(LRUCache* obj, int key) {
    CacheAddressLList *tempCA = obj->ct[returnHash(key,obj->capacity)].cacheAdd;
    int flag = 0;
    if (tempCA!=NULL){
        while(tempCA!=NULL){
            if (tempCA->key == key){
                flag = 1;
                break;
            }
            tempCA= tempCA->next;
    }
        if (flag == 1){
            int result = tempCA->cache->value;
            popCache(obj,tempCA);
            obj->currentSize+=1;
            return(result);
            

        }else{ 
            return -1;
        }
    }else{
        return -1;
    }
   
}

void lRUCacheFree(LRUCache* obj) {
    free(obj);
}

int main(){
    LRUCache *l1 = lRUCacheCreate(2);
    lRUCachePut(l1,1,1);
    lRUCachePut(l1,2,2);
    lRUCachePut(l1,11,6);
    // lRUCachePut(l1,1,4);

    printf("%d\n", lRUCacheGet(l1,1));
    printf("%d\n", lRUCacheGet(l1,11));
    lRUCacheFree(l1);
    // lRUCachePut(l1,11,6);
    // printf("%d\n", lRUCacheGet(l1,2));
    // printf("%d\n", lRUCacheGet(l1,1));
    // lRUCachePut(l1,1,4);
    // lRUCachePut(l1,1,5);
    

    // printf("%d\n", lRUCacheGet(l1,1));
    // printf("%d\n", lRUCacheGet(l1,2));
    // lRUCachePut(l1,2,3);
    // printf("%d\n", lRUCacheGet(l1,11));
    // printf("%d\n", lRUCacheGet(l1,1));
    // printf("%d\n", lRUCacheGet(l1,2));
    
    
}
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
    int hashCap;
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
    cache->hashCap = 20000;
    cache->ct = (CacheTable*)calloc(20000,sizeof(CacheTable));
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
    // lRUCacheGets(cache,-1);
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
    // return caL->cache;
}

int lRUCacheGet(LRUCache* obj, int key) {
    // if (obj->currentSize==0){return -1;}
    CacheAddressLList *tempCA = obj->ct[returnHash(key,obj->hashCap)].cacheAdd;
    // printf("%d, %d: %d\n",obj->head->key,obj->head->next->key,key);
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
            // CacheLList* t1 = obj->head;
            // printf("\nhelloWOrld\n");
            // while (obj->head->key!= tempCA->cache->key){
            //     obj->head = obj->head->next;
            // }
            if (tempCA->cache->prev != NULL){
                tempCA->cache->prev->next = tempCA->cache->next;
                tempCA->cache->next->prev = tempCA->cache->prev;
                tempCA->cache->next = obj->head;
                obj->head->prev = tempCA->cache;
                tempCA->cache->prev = NULL;
            }
            obj->head = tempCA->cache;
            
            // popCache(obj,tempCA);
            // obj->currentSize+=1;
            return(result);
        }

        else{ 
            return -1;
        }
    }else{
        return -1;
    } 
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
                    temp->prev = NULL;
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
    if (temp != NULL){
        while (temp->prev!=NULL ){
            temp = temp->prev;
        }
    }
    
    return temp;
    
    
}
void popCacheFull(LRUCache* obj){
    int key = obj->tail->prev->key;
    obj->ct[returnHash(key,obj->hashCap)].cacheAdd = popHashTable(obj->ct[returnHash(key,obj->hashCap)].cacheAdd,key);
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

    if (obj->ct[returnHash(key,obj->hashCap)].cacheAdd == NULL){
        obj->ct[returnHash(key,obj->hashCap)].cacheAdd = (CacheAddressLList*)calloc(1, sizeof(CacheAddressLList));
        obj->ct[returnHash(key,obj->hashCap)].cacheAdd->key = key;
        obj->ct[returnHash(key,obj->hashCap)].cacheAdd->next = NULL;
        obj->ct[returnHash(key,obj->hashCap)].cacheAdd->prev = NULL;
        obj->ct[returnHash(key,obj->hashCap)].cacheAdd->cache = (CacheLList*)calloc(1,sizeof(CacheLList));

        if (obj->head->value == -1){
            // obj->head->value = value;
            // *(obj->ct[returnHash(key,cap)].cacheAdd->cache) = *(obj->head);
            if (obj->currentSize >= cap) popCacheFull(obj);
            pushCache(obj,obj->ct[returnHash(key,obj->hashCap)].cacheAdd,value,key);
            // obj->tail->prev = obj->head;
            // obj->head->next = obj->tail;
            
        }else{
            if (obj->currentSize >= cap) popCacheFull(obj);
            pushCache(obj,obj->ct[returnHash(key,obj->hashCap)].cacheAdd,value,key);
            // obj->ct[returnHash(key,cap)].c->prev = (CacheLList*)calloc(1,sizeof(CacheLList));
            
        }   
    }
    else{
        // int i = 0;
        int flag = 0;
        CacheAddressLList *tempCA = obj->ct[returnHash(key,obj->hashCap)].cacheAdd;

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
        CacheAddressLList* a;
        if (flag == 1){
            CacheLList* t1 = obj->head;
            // while (obj->head->key!= tempCA->cache->key){
            //     obj->head = obj->head->next;
            // }
            if (tempCA->cache->prev != NULL){
                tempCA->cache->prev->next = tempCA->cache->next;
                tempCA->cache->next->prev = tempCA->cache->prev;
                tempCA->cache->next = obj->head;
                obj->head->prev = tempCA->cache;
                tempCA->cache->prev = NULL;
            }
            tempCA->cache->value = value;
            obj->head = tempCA->cache;
            obj->currentSize-=1;
            // tempCA->cache->value = value;
            // popCache(obj,tempCA,value);
        }
        else{ 
            if (obj->currentSize >= cap) 
            {
                popCacheFull(obj);

            }
            int x= 0;

            if (obj->ct[returnHash(key,obj->hashCap)].cacheAdd == NULL){
                obj->ct[returnHash(key,obj->hashCap)].cacheAdd = (CacheAddressLList*)calloc(1, sizeof(CacheAddressLList));
                
                obj->ct[returnHash(key,obj->hashCap)].cacheAdd->key = key;
                obj->ct[returnHash(key,obj->hashCap)].cacheAdd->cache = (CacheLList*)calloc(1,sizeof(CacheLList));
                obj->ct[returnHash(key,obj->hashCap)].cacheAdd->prev = NULL;
                obj->ct[returnHash(key,obj->hashCap)].cacheAdd->next = NULL;
                pushCache(obj,obj->ct[returnHash(key,obj->hashCap)].cacheAdd ,value,key);
                
            }else{
                tempCA = obj->ct[returnHash(key,obj->hashCap)].cacheAdd;
                while(obj->ct[returnHash(key,obj->hashCap)].cacheAdd!=NULL){
                    if (obj->ct[returnHash(key,obj->hashCap)].cacheAdd->key == key){
                        flag = 1;
                        break;
                    }
                    // i+=1;
                    if (obj->ct[returnHash(key,obj->hashCap)].cacheAdd->next == NULL){
                        break;
                    }
                    x+=1;
                    obj->ct[returnHash(key,obj->hashCap)].cacheAdd= obj->ct[returnHash(key,obj->hashCap)].cacheAdd->next;

                }
                obj->ct[returnHash(key,obj->hashCap)].cacheAdd->next  = (CacheAddressLList*)calloc(1, sizeof(CacheAddressLList));;
                obj->ct[returnHash(key,obj->hashCap)].cacheAdd->next ->key = key;
                obj->ct[returnHash(key,obj->hashCap)].cacheAdd->next ->cache = (CacheLList*)calloc(1,sizeof(CacheLList));
                obj->ct[returnHash(key,obj->hashCap)].cacheAdd->next->prev = obj->ct[returnHash(key,obj->hashCap)].cacheAdd;
                pushCache(obj,obj->ct[returnHash(key,obj->hashCap)].cacheAdd->next ,value,key);

                while (obj->ct[returnHash(key,obj->hashCap)].cacheAdd->prev != NULL){
                    obj->ct[returnHash(key,obj->hashCap)].cacheAdd =obj->ct[returnHash(key,obj->hashCap)].cacheAdd->prev;
                }
                
            }    
            
        }

    }
    obj->currentSize+=1;
}



void lRUCacheFree(LRUCache* obj) {
    free(obj);
}
typedef union inputData{
    int data1[1];
    int data2[2];

}inputData;

int main(){

    char* input1[] = {"put","put","put","put","put","get","put","get","get","put","get","put","put","put","get","put","get","get","get","get","put","put","get","get","get","put","put","get","put","get","put","get","get","get","put","put","put","get","put","get","get","put","put","get","put","put","put","put","get","put","put","get","put","put","get","put","put","put","put","put","get","put","put","get","put","get","get","get","put","get","get","put","put","put","put","get","put","put","put","put","get","get","get","put","put","put","get","put","put","put","get","put","put","put","get","get","get","put","put","put","put","get","put","put","put","put","put","put","put"};
    int* input2[] = {(int[]){10,13},(int[]){3,17},(int[]){6,11},(int[]){10,5},(int[]){9,10},(int[]){13},(int[]){2,19},(int[]){2},(int[]){3},(int[]){5,25},(int[]){8},(int[]){9,22},(int[]){5,5},(int[]){1,30},(int[]){11},(int[]){9,12},(int[]){7},(int[]){5},(int[]){8},(int[]){9},(int[]){4,30},(int[]){9,3},(int[]){9},(int[]){10},(int[]){10},(int[]){6,14},(int[]){3,1},(int[]){3},(int[]){10,11},(int[]){8},(int[]){2,14},(int[]){1},(int[]){5},(int[]){4},(int[]){11,4},(int[]){12,24},(int[]){5,18},(int[]){13},(int[]){7,23},(int[]){8},(int[]){12},(int[]){3,27},(int[]){2,12},(int[]){5},(int[]){2,9},(int[]){13,4},(int[]){8,18},(int[]){1,7},(int[]){6},(int[]){9,29},(int[]){8,21},(int[]){5},(int[]){6,30},(int[]){1,12},(int[]){10},(int[]){4,15},(int[]){7,22},(int[]){11,26},(int[]){8,17},(int[]){9,29},(int[]){5},(int[]){3,4},(int[]){11,30},(int[]){12},(int[]){4,29},(int[]){3},(int[]){9},(int[]){6},(int[]){3,4},(int[]){1},(int[]){10},(int[]){3,29},(int[]){10,28},(int[]){1,20},(int[]){11,13},(int[]){3},(int[]){3,12},(int[]){3,8},(int[]){10,9},(int[]){3,26},(int[]){8},(int[]){7},(int[]){5},(int[]){13,17},(int[]){2,27},(int[]){11,15},(int[]){12},(int[]){9,19},(int[]){2,15},(int[]){3,16},(int[]){1},(int[]){12,17},(int[]){9,1},(int[]){6,19},(int[]){4},(int[]){5},(int[]){5},(int[]){8,1},(int[]){11,7},(int[]){5,2},(int[]){9,28},(int[]){1},(int[]){2,2},(int[]){7,4},(int[]){4,22},(int[]){7,24},(int[]){9,26},(int[]){13,28},(int[]){11,26}};
    LRUCache *l1 = lRUCacheCreate(10);
    for (int i =0; i<sizeof(input1)/sizeof(input1[0]); i++){
        if (input1[i][0] == 'p'){
            lRUCachePut(l1,input2[i][0],input2[i][1]);
        }else{
             printf("%d\n", lRUCacheGet(l1,input2[i][0]));
        }
    }
    // lRUCachePut(l1,2,1);
    // lRUCachePut(l1,2,2);
    // printf("%d\n", lRUCacheGet(l1,2));
    // lRUCachePut(l1,1,1);
    // lRUCachePut(l1,4,1);
    // printf("%d\n", lRUCacheGet(l1,2));
    
    // printf("%d\n", lRUCacheGet(l1,1));
    // printf("%d\n", lRUCacheGet(l1,3));
    // printf("%d\n", lRUCacheGet(l1,4));
    // lRUCachePut(l1,3,3);
    // lRUCachePut(l1,11,6);

    // lRUCacheGets(l1,3);
    // printf("%d\n", lRUCacheGet(l1,11));
    // printf("%d\n", lRUCacheGet(l1,3));
    // printf("%d\n", lRUCacheGet(l1,1));
    // printf("%d\n", lRUCacheGet(l1,2));
    // printf("%d\n", lRUCacheGet(l1,1));
    // lRUCachePut(l1,3,3);
    
    // lRUCachePut(l1,4,4);
    // lRUCachePut(l1,5,5);
    // lRUCachePut(l1,6,6);
    // lRUCachePut(l1,3,7);
    // lRUCachePut(l1,6,8);
    // lRUCachePut(l1,9,9);
    // lRUCachePut(l1,12,9);

    // printf("%d\n", lRUCacheGet(l1,1));
    // printf("%d\n", lRUCacheGet(l1,3));
    // printf("%d\n", lRUCacheGet(l1,9));
    // lRUCachePut(l1,1,4);

    
    // printf("%d\n", lRUCacheGet(l1,11));
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
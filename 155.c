#include <stdio.h>
#include <stdlib.h>

typedef struct Stack{
    int num;
    struct Stack* next;
    struct Stack* min;
} Stack;

typedef struct {
    Stack *head;
    // Stack *min;
} MinStack;


MinStack* minStackCreate() {
    MinStack *stack = (MinStack *)calloc(1, sizeof(MinStack));
    stack->head = NULL;
    // stack->min = (Stack*)calloc(30000, sizeof(Stack));
    return stack;
}

void minStackPush(MinStack* obj, int val) {
    if (obj->head == NULL){
      obj-> head = (Stack*)calloc(1, sizeof(Stack));
      obj->head->num = val;
      obj->head->next = NULL;
      obj->head->min = obj->head;
    }else{
      Stack* temp = (Stack*)calloc(1, sizeof(Stack));
      temp -> num = val;
      temp -> next = obj->head;
      temp->min = (Stack*)calloc(1, sizeof(Stack));
      if(obj->head->min->num > val) temp->min = temp;
      else (temp->min) = (obj->head->min);
      obj->head = temp;
    }
}

void minStackPop(MinStack* obj) {
    obj->head = obj->head->next;
}

int minStackTop(MinStack* obj) {
    return obj->head->num;
}

int minStackGetMin(MinStack* obj) {
    return obj->head->min->num;
}

void minStackFree(MinStack* obj) {
    free(obj);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);
 
 * minStackPop(obj);
 
 * int param_3 = minStackTop(obj);
 
 * int param_4 = minStackGetMin(obj);
 
 * minStackFree(obj);
*/
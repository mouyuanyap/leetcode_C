#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct numberLL {
    int num;
    struct numberLL* next;
    struct numberLL* prev;
};

bool isPalindrome(int x){
    if (x<0) {
        return false;
    }
    else if (x>0 && x<10){
        return true;
    }else{
        int a, y;
        y = x;
        struct numberLL* head = (struct numberLL*)malloc(sizeof(struct numberLL));
        struct numberLL* tail = (struct numberLL*)malloc(sizeof(struct numberLL));
        head-> prev = NULL;
        tail-> next = NULL;
        head-> next = tail;
        tail-> prev = head;
        struct numberLL* move = (struct numberLL*)malloc(sizeof(struct numberLL));
        move = head;
        
        while (y!=0){
            
            struct numberLL* temp = (struct numberLL*)malloc(sizeof(struct numberLL));    
            temp->num = y%10;
            temp->next = move -> next;
            temp->prev = move;
            move->next->prev = temp;
            move->next = temp;
            move = move->next;

            y /=10;
        }
        head = head->next;
        tail = tail->prev;
        while (head->prev != tail && tail != head){
            if (head->num != tail->num) return false;
            head = head->next;
            tail = tail->prev;
        }
        return true;
    }


}

int main(){
    if (isPalindrome(10)){
        printf("true");
    }
    else {
        printf("false");
    }
}
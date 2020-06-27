#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct e{
    char* name;
    int length;
    struct e* next;
};
typedef struct e* element;

struct q{
    //  o -> o -> o -> o
    //  ^de            ^en
    element en;   // 指向要加入的那端
    element de;   // 指向要取出的那端
};
typedef struct q* queue;

void enqueue(queue* this, element e){
    // 如果該佇列為空就新增一個佇列
    if(!(*this)){
        queue new = malloc(sizeof(*new));
        new -> en = e;
        new -> de = e;
        *this = new;
        return;
    }

    // 於 en 的位址加入佇列
    (*this) -> en -> next = e;
    (*this) -> en = (*this) -> en -> next;
}

element dequeue(queue* this){

    if(*this == NULL){
        fprintf(stderr, "Queue is Empty\n");
        exit(EXIT_FAILURE);
    }

    element tmp = (*this) -> de;
    (*this) -> de = (*this) -> de -> next;

    // 佇列為空時直接將其設為 NULL 方便判斷其為空佇列
    if(!((*this) -> de)){
        *this = NULL;
    }
    return tmp;
}

void printQueueLn(queue this){
    element current;

    for(current = this->de; current; current = current->next){
        printf("%s (%d s)\t", current->name, current->length);
    }
    printf("\n");
}

element createElement(char* name, int len){
    element e = malloc(sizeof(*e));
    e -> name = name;
    e -> length = len;
    e -> next = NULL;
    return e;
}

int main(){
    element song1 = createElement("如果我們不曾相遇", 229);
    element song2 = createElement("盛夏光年", 349);
    element song3 = createElement("說散就散", 219);
    element song4 = createElement("金曜日のおはよう", 242);

    queue q = NULL;
    enqueue(&q, song1);
    printQueueLn(q);
    enqueue(&q, song2);
    printQueueLn(q);
    enqueue(&q, song3);
    printQueueLn(q);
    dequeue(&q);
    printQueueLn(q);
    dequeue(&q);
    printQueueLn(q);
    enqueue(&q, song4);
    printQueueLn(q);

    return 0;
}

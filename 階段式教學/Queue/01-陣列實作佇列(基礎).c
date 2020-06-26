#include<stdio.h>
#include<stdlib.h>

//指定這個佇列的長度
#define MAX_QUEUE_SIZE 100

//宣告一個長度為 MAX_QUEUE_SIZE 的全域變數 queue
int queue[MAX_QUEUE_SIZE];
int rear=-1;
int front=-1;
/*從 rear 插入元素，從 front 取出元素*/

void queueFull(){
    fprintf(stderr, "Queue is full\n");
    exit(EXIT_FAILURE);
}

void queueEmpty(){
    fprintf(stderr, "Queue is Empty\n");
    exit(EXIT_FAILURE);
}

//插入元素
void enqueue(int value){
    if(rear == MAX_QUEUE_SIZE - 1){
        queueFull();    //呼叫佇列已滿函式
    }
    queue[++rear] = value;
}

int dequeue(){
    if(front == rear){
        queueEmpty();   //呼叫佇列是空的函式
    }
    return queue[++front];
}

//方便我們觀察 Queue 變化
void printQueueLn(){
    int i;
    for(i=front+1; i<=rear; i++){
        printf("%d ",queue[i]);
    }
    printf("\n");
}

int main(){
    enqueue(10);
    printQueueLn();
    enqueue(20);
    printQueueLn();
    enqueue(30);
    printQueueLn();
    dequeue();
    printQueueLn();
    dequeue();
    printQueueLn();
    enqueue(40);
    printQueueLn();

    system("pause");
    return 0;
}

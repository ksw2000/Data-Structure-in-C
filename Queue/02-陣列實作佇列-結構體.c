#include <stdio.h>
#include <stdlib.h>

//指定這個佇列的長度
#define MAX_QUEUE_SIZE 100

// 佇列的型態不一定只放整數，而可能是結構體
// 因此我們用結構體改寫一次

struct e {
    char* name;
    int length;
};
typedef struct e element;

// 宣告一個長度為 MAX_QUEUE_SIZE 的全域變數 queue
element queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;
// 從 rear 插入元素，從 front 取出元素

void queueFull() {
    fprintf(stderr, "Queue is full\n");
    exit(EXIT_FAILURE);
}

void queueEmpty() {
    fprintf(stderr, "Queue is Empty\n");
    exit(EXIT_FAILURE);
}

// 插入元素
void enqueue(element value) {
    if (rear == MAX_QUEUE_SIZE - 1) {
        queueFull();  // 呼叫佇列已滿函式
    }
    queue[++rear] = value;
}

element dequeue() {
    if (front == rear) {
        queueEmpty();  // 呼叫佇列為空的函式
    }
    return queue[++front];
}

// 方便我們觀察 Queue 變化
void printQueueLn() {
    int i;
    for (i = front + 1; i <= rear; i++) {
        printf("%s(%d s)\t", queue[i].name, queue[i].length);
    }
    printf("\n");
}

int main() {
    element song1 = {"如果我們不曾相遇", 229};
    element song2 = {"盛夏光年", 349};
    element song3 = {"說散就散", 219};
    element song4 = {"金曜日のおはよう", 242};

    enqueue(song1);
    printQueueLn();
    enqueue(song2);
    printQueueLn();
    enqueue(song3);
    printQueueLn();
    dequeue();
    printQueueLn();
    dequeue();
    printQueueLn();
    enqueue(song4);
    printQueueLn();

    system("pause");
    return 0;
}

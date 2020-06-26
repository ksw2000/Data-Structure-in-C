#include<stdio.h>
#include<stdlib.h>

//指定這個環狀佇列的長度
#define MAX_QUEUE_SIZE 100

/*
    尤於如果只是一昧的往前移動佇列容易滿
    而且浪費空間
    因此我們可以用環狀佇列來實現
*/

struct e{
    char* name;
    int length;
};
typedef struct e element;

//宣告一個長度為 MAX_QUEUE_SIZE 的全域變數 queue
element queue[MAX_QUEUE_SIZE];
int rear = 0;
int front = 0;
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
void enqueue(element value){
    // 如果 rear 現在是 99 那下一次就是塞到 0
    // rear = (99+1) % 100 = 0
    /*
        當然也可以寫成
        if(rear == MAX_QUEUE_SIZE -1)
            rear = 0;
    */
    rear = (rear+1) % MAX_QUEUE_SIZE;

    /*
       當 「新的rear」 == front 時這時環狀佇列就是滿的
       比如現在 queue 長度有 4
        0  0  _ _ _ _
        0  1  _ A _ _ (enqueue完)
        0  2  _ A B _ (enqueue完)
        0  3  _ A B C (enqueue完)

        此時若我想要再 enqueue 是不行的
        因為當
        1  1  D A B C
        這種情況出現我們 rear 會等於 front
        這個條件已經被我們拿去當作判斷空佇列的標準了

        為了方便我們認定這個queue已經滿了
        因此長度 4 的 queue 事實上只能裝 3 個
    */
    if(rear == front){
        queueFull();    //呼叫佇列已滿函式
    }
    queue[rear] = value;
}

element dequeue(){
    if(front == rear){
        queueEmpty();   //呼叫佇列是空的函式
    }
    element tmp = queue[front];
    front = (front+1) % MAX_QUEUE_SIZE;
    return tmp;
}

//方便我們觀察 Queue 變化
void printQueueLn(){
    int i;
    for(i=front+1; i<=rear; i++){
        printf("%s(%d s)\t", queue[i].name, queue[i].length);
    }
    printf("\n");
}

int main(){
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

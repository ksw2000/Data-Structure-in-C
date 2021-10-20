#include <stdio.h>
#include <stdlib.h>

/*
    本範例利用大量 C 語言技巧，僅供參考，初學者建議跳過
    用靜態陣列和鍵結串列實作在演算法效能上都不是好方法
    因此此支程式盡可能著重在佇列的效能及封裝上
*/

typedef struct e* Element;
typedef struct q* Queue;

struct e {
    char* name;
    int length;
};

// 開頭變數 _ 表示 private
struct q {
    int _cap;
    int _rear;
    int _len;
    int _front;
    Element* list;
    void (*enqueue)(Queue, Element);
    Element (*dequeue)(Queue);
    int (*isEmpty)(Queue);
    void (*print)(Queue);
};

void enqueue(Queue this, Element e) {
    if ((this->_len + 1) == (this->_cap)) {
        int newCap = this->_cap << 1;
        Element* newList = malloc(sizeof(*newList) * newCap);
        int i;
        for (i = 0; i < this->_len; i++) {
            newList[i] = this->list[(this->_rear + i) % this->_cap];
        }
        this->list = newList;
        this->_front = this->_len;
        this->_rear = 0;
        this->_cap = newCap;
    }

    this->list[this->_front] = e;
    this->_front = (this->_front + 1) % this->_cap;
    this->_len++;
}

Element dequeue(Queue this) {
    if (this->isEmpty(this)) {
        fprintf(stderr, "Queue is empty");
        exit(EXIT_FAILURE);
    }
    Element tmp = this->list[this->_rear];
    this->_rear = (this->_rear + 1) % this->_cap;
    this->_len--;
    return tmp;
}

int isEmpty(Queue this) {
    return this->_len == 0;
}

void queuePrint(Queue this) {
    int i;
    Element e;
    for (i = 0; i < this->_len; i++) {
        e = this->list[(this->_rear + i) % this->_cap];
        printf("%s (%d min %d s) -> ", e->name, e->length / 60, e->length % 60);
    }
    printf("NULL\n");
}

Queue __Queue__() {
    Queue this = malloc(sizeof(*this));
    this->_cap = 8;
    this->_len = 0;
    this->_rear = 0;
    this->_front = 0;
    this->list = malloc(this->_cap * sizeof(*(this->list)));
    this->enqueue = enqueue;
    this->dequeue = dequeue;
    this->isEmpty = isEmpty;
    this->print = queuePrint;
    return this;
}

Element createElement(char* name, int len) {
    Element e = malloc(sizeof(*e));
    e->name = name;
    e->length = len;
    return e;
}

int main() {
    Queue q = __Queue__();
    Element song1 = createElement("如果我們不曾相遇", 229);
    Element song2 = createElement("盛夏光年", 349);
    Element song3 = createElement("說散就散", 219);
    Element song4 = createElement("金曜日のおはよう", 242);
    Element song5 = createElement("SOLO", 169);
    Element song6 = createElement("體面", 278);
    Element song7 = createElement("可愛くなりたい", 252);
    Element song8 = createElement("如煙", 319);

    q->enqueue(q, song1);
    q->print(q);
    printf("dequeue\n");
    q->dequeue(q);
    q->print(q);
    q->enqueue(q, song2);
    q->print(q);
    printf("dequeue\n");
    q->dequeue(q);
    q->print(q);
    q->enqueue(q, song3);
    q->print(q);
    q->enqueue(q, song4);
    q->print(q);
    printf("dequeue\n");
    q->dequeue(q);
    q->print(q);
    q->enqueue(q, song5);
    q->print(q);
    q->enqueue(q, song6);
    q->print(q);
    q->enqueue(q, song7);
    q->print(q);
    q->enqueue(q, song8);
    q->print(q);
    q->enqueue(q, song8);
    q->enqueue(q, song8);
    q->enqueue(q, song8);
    q->enqueue(q, song8);
    q->enqueue(q, song8);
    q->enqueue(q, song8);
    q->enqueue(q, song8);
    q->enqueue(q, song8);
    q->enqueue(q, song8);
    q->enqueue(q, song8);
    q->enqueue(q, song8);
    q->enqueue(q, song8);
    q->enqueue(q, song8);
    q->enqueue(q, song8);
    q->enqueue(q, song8);
    q->enqueue(q, song8);
    q->enqueue(q, song8);
    q->enqueue(q, song8);
    q->enqueue(q, song8);
    q->enqueue(q, song8);
    q->enqueue(q, song8);
    q->enqueue(q, song8);
    q->enqueue(q, song8);
    q->enqueue(q, song8);
    q->enqueue(q, song8);
    q->print(q);
    return 0;
}

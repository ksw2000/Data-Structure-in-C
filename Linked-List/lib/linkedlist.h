/*
    LinkedList
        Node* first: 指向串列開頭
        Node* last:  指向串列結尾
        Node append(LinkedList* this, void* data): 加入新節點(並返回節點位置)

    Node
        void* data:  節點內容(泛型指標)
        Node* next:  指向下一個結點

    __LinkedList__() 創建新的鍵結串列
*/

typedef struct node {
    void* data;
    struct node* next;
}Node;

typedef struct ll {
    Node* first;
    Node* last;
    Node* (*append)(struct ll*, void*);
}LinkedList;

Node* linkedlistAppend(LinkedList* this, void* data) {
    Node* n = malloc(sizeof(Node));
    n->data = data;
    n->next = NULL;
    if (!this->first) {
        this->first = n;
        this->last = n;
        return n;
    }
    this->last->next = n;
    this->last = this->last->next;
    return n;
}

LinkedList* __LinkedList__() {
    LinkedList* list = malloc(sizeof(LinkedList));
    list->first = NULL;
    list->last = NULL;
    list->append = linkedlistAppend;
    return list;
}

/*
    LinkedList
        Node* first: 指向串列開頭
        Node* last:  指向串列結尾
        Node append(LinkedList his, void* data): 加入新節點(並返回節點位置)

    Node
        void* data:  節點內容(泛型指標)
        Node* next:  指向下一個結點

    LinkedList __LinkedList__() 創建新的鍵結串列
*/
typedef struct node* Node;
typedef struct ll* LinkedList;

struct node {
    void* data;
    struct node* next;
};

struct ll {
    Node first;
    Node last;
    Node (*append)(struct ll*, void*);
};

Node linkedlistAppend(LinkedList this, void* data) {
    Node n = malloc(sizeof(*n));
    n->data = data;
    n->next = NULL;
    //如果為空串列
    if (!this->first) {
        this->first = n;
        this->last = n;
        return n;
    }
    this->last->next = n;
    this->last = this->last->next;
    return n;
}

LinkedList __LinkedList__() {
    LinkedList list = malloc(sizeof(*list));
    list->first = NULL;
    list->last = NULL;
    list->append = linkedlistAppend;
    return list;
}

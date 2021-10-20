// 取得「環狀鍵結串列」長度
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};
typedef struct node* Node;

void insertFront(Node* last, Node insertThis) {
    if (!(*last)) {
        *last = insertThis;
        insertThis->next = insertThis;
    } else {
        insertThis->next = (*last)->next;
        (*last)->next = insertThis;
    }
}

Node createNode(int data) {
    Node n = malloc(sizeof(*n));
    n->data = data;
    n->next = NULL;
    return n;
}

int length(Node last) {
    int count = 0;
    Node current;
    if (last) {
        for (current = last->next; current != last; current = current->next) {
            count++;
        }
        //最後一個會沒算到
        count++;
    }
    return count;
}

int main() {
    Node A = createNode(10);
    Node B = createNode(20);
    Node C = createNode(30);
    Node D = createNode(40);
    Node E = createNode(50);
    Node F = createNode(60);

    Node last = NULL;
    insertFront(&last, A);
    insertFront(&last, B);
    insertFront(&last, C);

    // C -> B -> A
    printf("該環狀鍵結串列長度：%d\n", length(last));

    insertFront(&last, D);
    insertFront(&last, E);
    insertFront(&last, F);

    // F -> E -> D -> C -> B -> A
    printf("該環狀鍵結串列長度：%d\n", length(last));

    last = NULL;
    printf("該環狀鍵結串列長度：%d\n", length(last));

    return 0;
}

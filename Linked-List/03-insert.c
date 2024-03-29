// 在 Linked list 中的其中一個 Node 後插入一個新的 Node
#include <stdio.h>
#include <stdlib.h>
#include "lib/linkedlist.h"

void insert(LinkedList* l, Node* insertAfterHere, char* insertThis) {
    // 檢查該佇列是否為空
    // 該佇列不為空
    if (l->first) {
        Node* newNode = malloc(sizeof(Node));
        newNode->data = (void*)insertThis;
        newNode->next = insertAfterHere->next;
        insertAfterHere->next = newNode;
    } else {
        // 為空的話直接用先前寫好 append 語法就好了
        // 課本上的實作也類似，課本是直接更改指向 first 的那個 Node
        l->append(l, (void*)insertThis);
    }
}

void printList(LinkedList* l) {
    Node* current;
    for (current = l->first; current; current = current->next) {
        printf("%s -> ", (char*)(current->data));
    }
    printf("NULL\n");
}

int main() {
    LinkedList* l = __LinkedList__();

    Node* BAT = l->append(l, "BAT");
    Node* CAT = l->append(l, "CAT");
    Node* EAT = l->append(l, "EAT");
    Node* FAT = l->append(l, "FAT");
    Node* HAT = l->append(l, "HAT");

    // (1) 原先的串列
    printList(l);
    // OUTPUT: BAT -> CAT -> EAT -> FAT -> HAT -> NULL

    // (2) 在該串列的 CAT 與 EAT 中插入 DAT
    insert(l, CAT, "DAT");
    printList(l);
    // OUTPUT: BAT -> CAT -> DAT -> EAT -> FAT -> HAT -> NULL

    // (3) 新建空串列，空串列使用 insert 的效果
    LinkedList* m = __LinkedList__();
    insert(m, NULL, "DAT");
    printList(m);
    // OUTPUT: DAT -> NULL

    return 0;
}

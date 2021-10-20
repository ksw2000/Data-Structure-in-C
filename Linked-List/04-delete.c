// 在 Linked list 中刪除其中一個節點
#include <stdio.h>
#include <stdlib.h>
#include "lib/linkedlist.h"

void delete (LinkedList l, Node nodeBeforeTarget) {
    // nodeBeforeTarget 為 NULL 代表刪除第一個節點
    // nodeBeforeTarget 有值代表刪除的不是第一個節點
    if (nodeBeforeTarget) {
        Node target = nodeBeforeTarget->next;
        Node nodeAfterTarget = target->next;
        free(target);
        nodeBeforeTarget->next = nodeAfterTarget;
    } else {
        Node target = l->first;
        Node nodeAfterTarget = target->next;
        free(target);
        l->first = nodeAfterTarget;
    }
}

int main() {
    LinkedList l = __LinkedList__();

    Node BAT = l->append(l, "BAT");
    Node CAT = l->append(l, "CAT");
    Node EAT = l->append(l, "EAT");
    Node FAT = l->append(l, "FAT");
    Node HAT = l->append(l, "HAT");

    // 原先的串列
    Node current;
    for (current = l->first; current; current = current->next) {
        printf("%s -> ", (char*)(current->data));
    }
    printf("NULL\n\n");

    // 試刪除 CAT 後的 EAT
    delete (l, CAT);

    for (current = l->first; current; current = current->next) {
        printf("%s -> ", (char*)(current->data));
    }
    printf("NULL\n\n");

    // 試刪除頭結點 BAT
    // 因為 BAT 前沒有節點所以我們用 NULL 來代替 nodeBeforeTarget
    delete (l, NULL);

    for (current = l->first; current; current = current->next) {
        printf("%s -> ", (char*)(current->data));
    }
    printf("NULL\n\n");

    return 0;
}

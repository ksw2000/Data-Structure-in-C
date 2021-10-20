#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char data[4];
    struct node* next;
};
typedef struct node* Node;

void append(Node* first, Node* trail, char* str) {
    Node n = malloc(sizeof(*n));
    strcpy(n->data, str);
    n->next = NULL;
    // 如果為空串列
    if (!(*first)) {
        *first = n;
        *trail = n;
        return;
    }
    (*trail)->next = n;
    *trail = (*trail)->next;
}

void linkedListPrintLn(Node first) {
    Node current;
    for (current = first; current; current = current->next) {
        printf("%s -> ", current->data);
    }
    printf("NULL\n");
}

int main() {
    Node first, trail;
    first = trail = NULL;

    // 示範 linked list append (即佇列的功能)
    append(&first, &trail, "BAT");
    append(&first, &trail, "CAT");
    append(&first, &trail, "EAT");
    append(&first, &trail, "FAT");
    append(&first, &trail, "HAT");
    linkedListPrintLn(first);

    return 0;
}

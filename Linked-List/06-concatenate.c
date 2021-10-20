// 串接兩個 Linked list
#include <stdio.h>
#include <stdlib.h>
#include "lib/linkedlist.h"

LinkedList concatenate(LinkedList dest, LinkedList src) {
    // 當 dest 串列不為空時直接將來源其結尾 next 指向 src 串列的頭
    if (dest->first) {
        dest->last->next = src->first;
    } else {
        // 若 dest 為空則直接將 dest 的頭指向 src 的頭，dest的尾指向 src 的尾
        dest->first = src->first;
        dest->last = src->last;
    }
    return dest;
}

int main() {
    LinkedList l = __LinkedList__();
    l->append(l, "BAT");
    l->append(l, "CAT");
    l->append(l, "EAT");
    l->append(l, "FAT");

    printf("l: \t");
    Node current;
    for (current = l->first; current; current = current->next) {
        printf("%s -> ", (char*)(current->data));
    }
    printf("NULL\n");

    LinkedList m = __LinkedList__();
    m->append(m, "HAT");
    m->append(m, "JAT");
    m->append(m, "LAT");
    m->append(m, "MAT");

    printf("m: \t");
    for (current = m->first; current; current = current->next) {
        printf("%s -> ", (char*)(current->data));
    }
    printf("NULL\n");

    printf("l + m: \t");
    l = concatenate(l, m);
    for (current = l->first; current; current = current->next) {
        printf("%s -> ", (char*)(current->data));
    }
    printf("NULL\n");

    LinkedList s = __LinkedList__();
    printf("s: \t");
    for (current = s->first; current; current = current->next) {
        printf("%s -> ", (char*)(current->data));
    }
    printf("NULL\n");

    printf("s + m: \t");
    s = concatenate(s, m);
    for (current = s->first; current; current = current->next) {
        printf("%s -> ", (char*)(current->data));
    }
    printf("NULL\n");

    return 0;
}

// 反轉一個 Linked list
#include <stdio.h>
#include <stdlib.h>
#include "lib/linkedlist.h"

LinkedList* invert(LinkedList* l) {
    /*
        比較好懂的作法

        Node* newList;
        Node* current;
        Node* next;
        newList = NULL;
        for(current = l->first; current; current=next){
            // 暫時存著下一個 current 的位址
            next = current->next;

            // 將讀來的 node 以 push 的方式加入新的 Linked list
            current->next = newList;
            newList = current;
        }

        LinkedList* m = __LinkedList__();
        m->first = newList;
        m->last = l->first;

        return m;
    */

    // 課本作法
    Node* trail;
    Node* middle;
    Node* lead = l->first;
    middle = NULL;
    while (lead) {
        trail = middle;
        middle = lead;
        lead = lead->next;
        middle->next = trail;
    }

    LinkedList* m = __LinkedList__();
    m->first = middle;
    m->last = l->first;

    return m;

    /*
        課本實作上使用三個指標
        trail:  持續指向新的 linked list 的開頭
        middle: 暫時存取lead，並使lead接上trail
        lead:   走訪原本的 linked list

        while(lead){
            trail = middle;         // trail 暫存 middle
            middle = lead;          // middle 暫存 lead
            lead = lead->next;      // 每次迭代時 lead 走訪原串列的下個節點
            middle->next = trail    // 將走訪到的原串列節點加回新串列
        }

        課本上的作法非常精簡
        Fundamentals of Data Structure in C p.171 Program 4.16

        自己實作上建議可以將想法想成
        1. 走訪舊串列
        2. 走訪時將舊串列以 stack 的方式加入新串列
        3. 新串列即答案
    */
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
    l->append(l, "BAT");
    l->append(l, "CAT");
    l->append(l, "EAT");
    l->append(l, "FAT");
    l->append(l, "HAT");

    printf("original: \t");
    printList(l);
    // OUTPUT: BAT -> CAT -> EAT -> FAT -> HAT -> NULL

    LinkedList* m = invert(l);
    printf("inverted: \t");
    printList(m);
    // OUTPUT: HAT -> FAT -> EAT -> CAT -> BAT -> NULL

    return 0;
}

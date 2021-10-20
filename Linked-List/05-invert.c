// 反轉一個 Linked list
#include <stdio.h>
#include <stdlib.h>
#include "lib/linkedlist.h"

LinkedList invert(LinkedList l) {
    /*
        比較好懂的作法

        Node newList, current, next;
        newList = NULL;
        for(current = l->first; current; current=next){
            // 暫時存著下一個 current 的位址
            next = current->next;

            // 將讀來的 node 以 push 的方式加入新的 Linked list
            current->next = newList;
            newList = current;
        }

        LinkedList m = __LinkedList__();
        m->first = newList;
        m->last = l->first;

        return m;
    */

    // 課本作法
    Node trail, middle;
    Node lead = l->first;
    middle = NULL;
    while (lead) {
        trail = middle;
        middle = lead;
        lead = lead->next;
        middle->next = trail;
    }

    // 因為我用的是 OOP 所以又多的幾步 (記錄新串列開頭而已也沒什麼)
    LinkedList m = __LinkedList__();
    m->first = middle;
    m->last = l->first;

    return m;

    /*
        課本實作上使用三個指標
        trail:  持續指向新的 linked list 的開頭
        middle: 暫時存取lead，並使lead接上trail
        lead:   走訪原本的 linked list

        while(lead){
            trail = middle;         // [STEP2] trail 暫存 middle
       (保持在新串列的最前端) middle = lead;          // [STEP3] middle 暫存
       lead lead = lead->next;      // [STEP4] lead 走訪舊串列 middle->next =
       trail    // [STEP1] 將走訪到的舊串列節點加回新串列 (從前方加入(stack
       push))
        }

        課本上的作法實在過於精簡，只有神人才看得懂吧
        Fundamentals of Data Structure in C p.171 Program 4.16

        自己實作上建議可以將想法想成
        1. 走訪舊串列
        2. 走訪時將舊串列以 stack 的方式加入新串列
        3. 新串列即答案
    */
}

int main() {
    LinkedList l = __LinkedList__();
    l->append(l, "BAT");
    l->append(l, "CAT");
    l->append(l, "EAT");
    l->append(l, "FAT");
    l->append(l, "HAT");

    printf("l: \t");
    Node current;
    for (current = l->first; current; current = current->next) {
        printf("%s -> ", (char*)(current->data));
    }
    printf("NULL\n");

    LinkedList m = invert(l);

    printf("m: \t");
    for (current = m->first; current; current = current->next) {
        printf("%s -> ", (char*)(current->data));
    }
    printf("NULL\n");
    return 0;
}

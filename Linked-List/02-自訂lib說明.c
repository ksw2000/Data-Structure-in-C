/*
    本範例利用大量 C 語言技巧
    初學者僅需了解 lib/linklist.h 的用法即可 (相信大家能用其他方式實作出來)
    本範例是為了提供以後範例能更簡單使用 Linked list 所編
*/

#include <stdio.h>
#include <stdlib.h>
#include "lib/linkedlist.h"
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
int main() {
    // 宣告新的 LinkedList
    LinkedList l = __LinkedList__();

    // 在 LinkedList l 中依序加入 BAT, CAT, EAT, FAT, HAT
    l->append(l, "BAT");
    l->append(l, "CAT");
    l->append(l, "EAT");
    l->append(l, "FAT");
    l->append(l, "HAT");

    // 結構體 LinkedList 中 first 指向 BAT, last 指向 HAT
    Node current;
    for (current = l->first; current; current = current->next) {
        printf("%s -> ", (char*)(current->data));
    }
    printf("NULL");

    // OUTPUT: BAT -> CAT -> EAT -> FAT -> HAT -> NULL

    return 0;
}

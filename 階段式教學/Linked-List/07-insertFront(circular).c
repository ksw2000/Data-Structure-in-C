// 在「環狀鍵結串列」的前方加入新節點
// 注意本範例使用的是「環狀鍵結串列」
#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node* next;
};
typedef struct node* Node;

void insertFront(Node* last, Node insertThis){
    //如果 *last 為 NULL (鍵結串列為空)
    if(!(*last)){
        *last = insertThis;
        insertThis->next = insertThis;
    }else{
        // insertThis->next = 該陣列最前方
        // 訪陣列最前方即最後方的 next
        // A → B → C → D
        // ↑ ← ← ← ← ← ↓
        insertThis -> next = (*last)->next;

        // 重新記錄陣列最前方是哪個點
        (*last)->next = insertThis;
    }
}

/*
    為什麼 insertFront 第一個參數要用 Node* 不用 Node？
    更直白的說，為什麼有些要用指標傳入，有些不用？
    因為當 lastnode 為空時我們必需要更動 lastnode 的值，即：

    *last = insertThis;

    如果我們用 Node 當參數傳入，我們無法直接更動其值，所以要用 Node*
*/

//該函數方便我們測試新的節點
Node createNode(int data){
    Node n = malloc(sizeof(*n));
    n->data = data;
    n->next = NULL;
    return n;
}

int main(){
    Node A = createNode(10);
    Node B = createNode(20);
    Node C = createNode(30);
    Node D = createNode(40);

    Node last = NULL;
    insertFront(&last, A);
    insertFront(&last, B);
    insertFront(&last, C);
    insertFront(&last, D);

    //走訪
    Node current;
    if(last){
        for(current = last->next; current!=last; current = current->next){
            printf("%d -> ", current->data);
        }
        current = last;
        printf("%d -> ", current->data);
    }

    printf("NULL\n");
    return 0;
}

// 參考 Fundmentals of data structures in c 2nd edition 第 177 頁
#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 24

enum boolean{
    FALSE, TRUE
};
typedef enum boolean bool;

struct node{
    int data;
    struct node* next;
};
typedef struct node *nodePointer;

int main(){
    short int out[MAX_SIZE];
    nodePointer seq[MAX_SIZE];  // 建立MAX_SIZE個陣列 (linked-list 堆疊)
    nodePointer x, y, top;
    int i, j, n;

    printf("Enter the size (<=%d)", MAX_SIZE);
    scanf("%d",&n);
    for(i=0; i<n; i++){
        // initialize seq and out
        out[i] = TRUE;  // 輸出時標記有沒有輸出過(可輸出標記為 TRUE)
        seq[i] = NULL;  // 初始化為空的 (linked-list 堆疊)
    }

    //phase 1: Input the equivalence pairs:
    do{
        printf("Enter a pair of number (-1 -1 to quit): ");
        scanf("%d %d", &i, &j);

        x = malloc(sizeof(*x));
        x -> data = j;
        x -> next = seq[i];
        seq[i] = x;

        x = malloc(sizeof(*x));
        x -> data = i;
        x -> next = seq[j];
        seq[j] = x;
    }while(i >= 0);
    /*
        seq[] 存放的樣的如下
        比如輸入 0 1
        [0] -> 1 -> NULL
        [1] -> 0 -> NULL
        [2] -> NULL
        [3] -> NULL
        ...

        再輸入 1 3
        [0] -> 3 -> 1 -> NULL
        [1] -> 0 -> NULL
        [2] -> NULL
        [3] -> 1 -> NULL
        ...
    */

    //phase 2: Output the equivalence classes:
    for(i=0; i<n; i++){
        if(out[i]){                 // 如果可印出(輸出)
            printf("\nNew class:%5d", i);
            out[i] = FALSE;         // 因為已印出，不可再輸出所以標記為 FALSE
            x = seq[i];
            top = NULL;             // 初始化堆疊
            for(;;){
                // 再 x 能走的情況盡可能往右走
                while(x){
                    j = x->data;
                    if(out[j]){
                        printf("%5d", j);
                        out[j] = FALSE;
                        y = x->next;    // (1)
                        x->next = top;  // (2)
                        top = x;        // (3)
                        x = y;          // (4)
                        /*
                            ## 注意 x->next 表示不同概念
                            ## x->next 在等號左側是 (b)
                            ## x->next 在等號右側是 (f)

                                x  (e)        x->next (f)
                            [ data (a)]      [data2 (c)]
                            [ next (b)] ->   [next2 (d)]

                            (1) 暫存 x->next (f)的位置
                            (2) 更動 (b) 的位置 (也就是為何 (1) 要暫存)
                            (3) top = x (e)
                            (4) x = y 其實也就是 (f)

                            (1)(4) 是為了讓 x 能繼續往下
                            (2)(3) 是為了形成 top 串鏈堆疊

                            也就是說在以印出的情況下
                            x 會往繼續往串列下方走 i.e. x 會從指向 (e) 被更動成 (f)
                            而 x 走過的地方的 next 值 (b) 部份 會被更動成 top 值
                            目的是為了形成 top 鏈
                            top 是為了提供其他可走訪的 node 所組成的 linked list

                            *****************************************************************
                            *  top 本身就是一個 linked list stack 只是他是用現有的 node 串起來 *
                            *****************************************************************

                            如果不用現有的空間另外開一個堆疊來實作也是可 (浪費記憶體)
                            課本提供的版本過於精簡，實在令人難懂，助教最愛出這種
                            所以有可能會挖空 (1)(2)(3)(4) 出成題目
                        */
                    }else{
                        x = x->next;
                    }
                }

                // 若 x 沒了就把 top 鏈 pop 出來
                if(!top){
                    break;
                }else{
                    x = seq[top->data]; // top->data 會儲存在這個 "equivalence" 中的值
                    top = top->next;    // top->next 會儲存上一個 top 值
                    // 可以回翻上一步的程式碼，應該能理解
                    // 我是覺得不太好理解了，我自己看了很多遍
                }
            }
        }
    }

    printf("\n");
    return 0;
}

/*
    測試測資
    6
    0 1
    1 3
    3 5
    2 4
*/

// For example
// [0] -> 1
// [1] -> 3 -> 0
// [2] -> 4
// [3] -> 5
// [4] -> 2
// [5] -> 3

// step1 從 0 走訪出 1  (現在 0 -> 1)
// top = (1, NULL)
// x 沒了，看 top

// 展開 top
// x = 1, top = NULL (top往下走)
// 從 1 走訪出 3        (現在 0 -> 1 -> 3)
// top = (3, NULL)
// 因為 x 還有，繼續往右走訪出 0 (走過了跳過)
// x 沒了，看 top

// 展開 top
// x = 3, top = NULL (top往下走)
// 從 3 走訪出 5        (現在 0 -> 1 -> 3 -> 5)
// top = (5, NULL)
// x 沒了，看 top

// 展開top
// x = 5 top = NULL (top往下走)
// 從 5 走訪到 3 (但走訪過了
// x 沒了，看 top
// top 也沒了

// 結果：0 -> 1 -> 3 -> 5
// 但還沒完，只走了一條
// 下一條從 1 開始(但 1 抓過)
// 所以從 2 開始 (直到最後一個數)

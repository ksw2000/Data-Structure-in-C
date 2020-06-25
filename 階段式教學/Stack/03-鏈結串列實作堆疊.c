#include<stdio.h>
#include<stdlib.h>

struct s{
    int val;
    struct s* next;
};

typedef struct s* stack;

void push(stack* oldStack, int val){
    //新增一個結構體，指向 原本的堆疊 內容為 val
    stack newElement = malloc(sizeof(*newElement));
    newElement->val = val;
    newElement->next = *oldStack;

    //將 oldStack 的內容換成換成 newElement
    //因為這一步的關係我們才需要用到 stack*
    //因為函數無法直接更改區域變數的值，但可以透過指標
    //如果oldStack是全域變數則另當別論

    *oldStack = newElement;
}

int pop(stack* oldStack){
    stack tmp;  //用來儲存即將被 free 掉的記憶體位置
    int ret;    //用來儲存要被 pop出的值
    tmp=*oldStack;
    ret=(*oldStack)->val;
    *oldStack=(*oldStack)->next;
    free(tmp);
    return ret;
}

//印出堆疊裡的值
//不需要改變 s 的值所以參數只要 stack 不用 stack*
void printStackLn(stack s){
    stack current;
    //這個for迴圈可能不好懂，可以回去複習一下
    //https://github.com/Hadname/data_structure_in_C/blob/master/%E9%9A%8E%E6%AE%B5%E5%BC%8F%E6%95%99%E5%AD%B8/README.md
    for(current=s; current; current=current->next){
        printf("%d ",current->val);
    }
    printf("\n");
    /*
        1. current = s
        2. 判斷 current 是不是 0
        3. 如果判斷是是「非0」就進入 for 迴圈 print 東西出來
        4. 將 current 指向下一個 next
        5. 重複 2~4
    */
    /*
        注意！
        如果一個指標 p 是 null
        你卻硬要取出東西比如 p->val
        程式會直接閃退，而且一般編譯器不會噴錯
        這時可以在程式碼各處print一些東西出來，建議是行號
        比如：第10行有印出來而第15行沒有被印出來
        就可以確認是10~15行中的程式碼出現問題
        這是一個可以縮小範圍檢查程式碼的方法
    */
}

int main(){
    stack foo=NULL;
    //為什麼要設為 NULL 呢？
    //如果一開始沒有將 foo 指向 NULL
    //則該鏈結串列的最後一個結構體的next會指向一個殘值
    //此時 printStackLn() 內的for迴圈，會無法判斷何時要結束
    //造成程式出錯

    push(&foo, 10);
    printStackLn(foo);
    push(&foo, 20);
    printStackLn(foo);
    push(&foo, 30);
    printStackLn(foo);
    pop(&foo);
    printStackLn(foo);
    pop(&foo);
    printStackLn(foo);
    push(&foo, 40);
    printStackLn(foo);

    /*
        眼尖的學弟妹可能會注意到這裡的
        push() pop() printStackLn()
        都有 stack 的參數而前面 01 02 兩支都沒有
        那是因為前面2支的 stack 都是宣告在全域變數的範圍
        函數直接取用，所以不需要 stack 的值

        這支程式碼比前面 01 02 都方便
        再未來講解其他題目時，我們直接把他存成 .h 方便使用
    */
    system("pause");
    return 0;
}

/*
    這支程式的邏輯是從其他資料結構的書微調來的
    教授指定用書並沒有這種寫法
*/

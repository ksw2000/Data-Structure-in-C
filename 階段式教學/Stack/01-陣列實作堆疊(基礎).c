#include<stdio.h>
#include<stdlib.h>

//指定這個陣列的長度
#define MAX_STACK 100

//宣告一個長度為 MAX_STACK 的全域變數 stack
int stack[MAX_STACK];

//top 設為 -1 : 代表 stack 裡面沒有資料，空空如也
//如果 stack[0] 有資料但再上面就沒有 top 就是 0
//如果 stack[1] 有資料但再上面就沒有 top 就是 1
//如果 stack[2] 有資料但再上面就沒有 top 就是 2
//...依此類推，所以一開始設成 -1 代表空空如也

int top=-1;

void push(int value){
    //因為最大只到 stack[MAX_STACK-1]
    //所以當 top == MAX_STACK-1 時
    if(top == MAX_STACK-1){
        fprintf(stderr,"Stack is full.");
        exit(EXIT_FAILURE);
    }
    stack[top+1]=value;
    top=top+1;
}

int pop(){
    //當 top == -1 時還要再抓東西出來，一定是抓不出來啊
    if(top==-1){
        fprintf(stderr,"Stack is empty.");
        exit(EXIT_FAILURE);
    }
    top-=1;
    return stack[top+1];
}

//方便我們觀察 stack 變化
void printStackLn(){
    int i;
    for(i=0; i<=top; i++){
        printf("%d ",stack[i]);
    }
    printf("\n");
}

int main(){
    push(10);
    printStackLn();
    push(20);
    printStackLn();
    push(30);
    printStackLn();
    pop();
    printStackLn();
    pop();
    printStackLn();
    push(40);
    printStackLn();

    return 0;
}

/*
    更精簡的寫法
    請先弄清 top++、++top 的區別

    (1)
    a = top++
    top 的值先傳給 a ; top 再加 1

    (2)
    a = ++top
    top 先加 1 ; top 的值再傳給 a

    以下是改寫過後更精簡的寫法：

    void push(int value){
        if(top == MAX_STACK-1){
            fprintf(stderr,"Stack is full.");
            exit(EXIT_FAILURE);
        }
        stack[++top]=value;
    }

    int pop(){
        if(top==-1){
            fprintf(stderr,"Stack is empty.");
            exit(EXIT_FAILURE);
        }
        return stack[top--];
    }
*/

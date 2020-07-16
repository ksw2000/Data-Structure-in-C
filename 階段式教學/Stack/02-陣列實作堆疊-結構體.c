#include<stdio.h>
#include<stdlib.h>

//指定這個陣列的長度
#define MAX_STACK 100

/*
    堆疊的型態不一定只放整數，而可能是結構體
    因此我們用結構體改寫一次
*/

struct e{
    char name[20];
    int atomic_number;
    double atomic_mass;
};

typedef struct e element;

//宣告一個長度為 MAX_STACK 的全域變數 stack
element stack[MAX_STACK];
int top=-1;

void push(element value){
    //因為最大只到 stack[MAX_STACK-1]
    //所以當 top == MAX_STACK-1 時
    if(top == MAX_STACK-1){
        fprintf(stderr,"Stack is full.");
        exit(EXIT_FAILURE);
    }
    stack[++top]=value;
}

element pop(){
    //當 top == -1 時還要再抓東西出來，一定是抓不出來啊
    if(top==-1){
        fprintf(stderr,"Stack is empty.");
        exit(EXIT_FAILURE);
    }
    return stack[top--];
}

//方便我們觀察 stack 變化
void printStackLn(){
    int i;
    for(i=0; i<=top; i++){
        printf("%s 質子數：%d 原子量：%lf ",stack[i].name,stack[i].atomic_number, stack[i].atomic_mass);
    }
    printf("\n");
}

int main(){
    element H = {"hydrogen",1,1.00794};

    /*
        語法等價於
        strcpy(H.name,"hydrogen");
        H.atomic_number=1;
        H.atomic_mass=1.00794;
    */

    push(H);
    printStackLn();

    element He = {"helium",2,4.002602};
    element Li = {"Lithos",3,6.941};

    push(He);
    printStackLn();
    push(Li);
    printStackLn();
    pop();
    printStackLn();
    pop();
    printStackLn();

    return 0;
}

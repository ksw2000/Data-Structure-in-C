#include<stdio.h>

void absolute(int* a){
    if( *a < 0 ){   //把 a 取出值來看，看是否小於 0
        *a = (*a)*(-1);
    }
}

void swap(int* a, int* b){
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}


int main(){
    //如何在main()之外的地方修改main之內的變數？
    //把變數的位置傳給main()之外的函數，只要有他們的外址就可以直接更動他們的值
    int num = -10;
    absolute(&num);  //abs() 接收到 num 的記憶體位置
    printf("num: %d\n", num);

    //進階試範 交換兩個變數
    int x=37, y=21;
    swap(&x, &y);   //swap() 接收 x 和 y 的記憶體位置
    printf("x: %d , y: %d", x, y);

    return 0;
}

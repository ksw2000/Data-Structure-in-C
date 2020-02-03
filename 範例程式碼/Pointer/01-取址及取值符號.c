#include<stdio.h>

int main(){
    int a=10;
    //利用 & 取得 a (型態為 int) 的位置
    printf("a的值 %d , a的記憶體位置 %p\n", a, &a);
    //使用 & 取址 &a (型態為 int*)

    int* pointerA;
    pointerA=&a;    //利用 & 取址後型態變成指標，可以懂嗎？

    //那麼如何從已存在的位置取值呢？
    //在指標變數前加上 * 就可以還原出原本的值哦哦哦！
    printf("pointerA 的值 (記憶體位置) %p , pointerA 位置上對應的值 %d",pointerA, *pointerA);
    //值用 * 取值 *pointerA (型態為 int)

    /*
        int  的東西前面加 & 會變成 int*
        int* 的東西前面加 * 會變回 int
    */
    
    return 0;
}

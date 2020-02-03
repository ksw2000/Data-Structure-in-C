#include<stdio.h>
#include<stdlib.h>
int main(){
    //觀察以下程式碼
    int arr[]={10,12,14,53,12,15};
    printf("arr[0]'s adress : %p\n", arr);
    printf("arr[1]'s adress : %p\n", arr+1);
    printf("arr[2]'s adress : %p\n", arr+2);

    //跟前一支程式比較是否有看出一些端倪？

    /*
        那一開始就宣告好的陣列和用動態記憶體宣告的陣列差在哪呢？
        差在使用的記憶體在不同區塊
        直接宣告好的陣列會在程式「執行時」就先決定好要用哪一塊，這塊記憶體在stack區。
        而利用malloc()決定的記憶體則時程式「執行中」才會取得的，這塊記憶體在heap區。
        只有heap區的記憶體可以回收再利用
        也就是說如果你在這支程式中加入 free(arr) 是沒有意義的
    */
    return 0;
}

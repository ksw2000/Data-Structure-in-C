#include<stdio.h>
#include<stdlib.h>

//如何動態地宣告二維陣列？
//此程式將試範動態宣告一個 9 * 5 的二維陣列

int main(){
    //STEP1: 宣告 int** 變數
    int** Array2D;

    //STEP2: 將 int** 指向 9 個 int*
    Array2D = malloc(sizeof(int*) * 9);

    //STEP3: 將每個 int* 再指向 5 個 int
    int i;
    for(i=0; i<9; i++){
        Array2D[i] = malloc(sizeof(int) * 5);
    }

    //完成

    //測試─將每個 element 編號
    int j,count=0;
    for(i=0; i<9; i++){
        for(j=0; j<5; j++){
            Array2D[i][j]=count;
            count++;
        }
    }

    //將每個 element 輸出
    for(i=0; i<9; i++){
        for(j=0; j<5; j++){
            printf("%2d ", Array2D[i][j]);
        }
        printf("\n");
    }

    return 0;
}

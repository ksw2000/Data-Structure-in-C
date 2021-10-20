#include<stdio.h>

struct rectangle{
    int height;
    int width;
};

//<第一種試範>
//area 函數將計算傳進來的結構體的面積
int area(struct rectangle data){
    return data.height * data.width;
}

// <第二種試範>
// 與第一種的差別在於，第二種用的是指標來取得 height 和 width
// 不需要把所有值都傳進函數裡面
int areaByPointer(struct rectangle* data){
    return data->height * data->width;
}

int main(){
    struct rectangle rec1;
    rec1.height=10;
    rec1.width=20;

    printf("rec1 的面積 area(rec1) = %d\n",area(rec1));
    printf("rec1 的面積 areaByPointer(&rec1) = %d\n",areaByPointer(&rec1));


    return 0;
}

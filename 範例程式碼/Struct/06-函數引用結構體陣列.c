#include<stdio.h>

struct rectangle{
    int height;
    int width;
};

//因為有學弟問所以補充一下

/* 計算 length 個長方型的面積合，array 代表陣列首的記憶體位置，也就是說
   array    表示 rec[0] 的記憶體位置
   array+1  表示 rec[1] 的記憶體位置
   array+2  表示 rec[2] 的記憶體位置
*/

int sumArea(struct rectangle* array, int length){
    int sum=0;
    int i;
    for(i=0; i<length; i++){
        sum += array[i].height * array[i].width;
    }
    return sum;
}

int main(){
    struct rectangle rec[3];

    // 10*10
    rec[0].height=10;
    rec[0].width=10;

    // 5*35
    rec[1].height=5;
    rec[1].width=35;

    // 7*18
    rec[2].height=7;
    rec[2].width=18;

    printf("三個長方型的面積合：%d", sumArea(rec, 3));

    return 0;
}

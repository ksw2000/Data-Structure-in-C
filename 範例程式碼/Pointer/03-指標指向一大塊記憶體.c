#include<stdio.h>
#include<stdlib.h>
int main(){
    //指標指向一大塊記憶體，比如 10 個 int 長
    int* arr;
    arr=malloc(sizeof(int)*10);

    //把10塊空間各別賦予值
    int i;
    for(i=0; i<10; i++){
        *(arr+i) = i;   //arr, arr+1, arr+2, ..., arr+9 共 10 塊空間
        // 我們為這10個空間賦予 0~9
    }
    //這可能有點不好懂，沒關係待會會講更容易的方法

    //我們把這個 arr 遍歷出來看看
    printf("遍歷arr\n");
    for(i=0; i<10; i++){
        printf("%d ",*(arr+i));
    }
    printf("\n");

    //------------------------------------------//

    //更直觀的方法(採用跟陣列一樣的方法)
    //這次我們換一種更直觀的方法賦值
    for(i=0; i<10; i++){
        arr[i] = i+1; // 為了與前一次區別這次我們為這10塊分別賦予 1~10
    }
    //我們再一次把這個 arr 遍歷出來看看
    printf("遍歷arr\n");
    for(i=0; i<10; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    //利用動態記憶體配置取得的空間可以用free()歸還給電腦
    free(arr);

    return 0;
}

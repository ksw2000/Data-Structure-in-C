#include <stdio.h>
#include <stdlib.h>
int main() {
    // 指標指向一大塊記憶體，比如 10 個 int 長
    int* arr;
    arr = malloc(sizeof(int) * 10);

    // 對 10 塊空間分別賦值
    int i;
    for (i = 0; i < 10; i++) {
        *(arr + i) = 10;  // arr, arr+1, arr+2, ..., arr+9 共 10 塊空間
        // 我們為這10個空間賦予 10
    }

    // 我們把這個 arr 遍歷出來看看
    printf("遍歷arr\n");
    for (i = 0; i < 10; i++) {
        printf("%d ", *(arr + i));
    }
    printf("\n");
    // Output: 10 10 10 10 10 10 10 10 10 10

    // 更直觀的方法(採用跟陣列一樣的方法)
    // 這次我們換一種更直觀的方法賦值
    for (i = 0; i < 10; i++) {
        arr[i] = 20;  // 為了與前一次區別這次我們為這 10 塊改成賦予 20
    }

    // 我們再一次把這個 arr 遍歷出來看看
    printf("遍歷arr\n");
    for (i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    // Output: 20 20 20 20 20 20 20 20 20 20

    // 利用動態記憶體配置取得的空間可以用free()歸還給電腦
    // 2021/10/20 請記得，只有動態配置的記憶體可以 free
    // 之前穆冠蓁直接把 stack 區 free 掉，笑死
    free(arr);

    return 0;
}

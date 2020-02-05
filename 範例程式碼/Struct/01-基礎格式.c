#include<stdio.h>

/*
    struct 可以當做把一堆類似的變數綁定起來
    比如我現在有個叫「長方形」的結構體，裡面包含兩項，分項是長與寬

    可參考
    http://gundambox.github.io/2015/10/30/C%E8%AA%9E%E8%A8%80-struct%E3%80%81union%E3%80%81enum/
*/
struct rectangle{
    int height;
    int width;
};

int main(){
    //struct rectangle 變成一個新的型態，就像 int, float 一樣
    //假設我們有三個長方型 a,b,c
    /*其中
        a: 20*10
        b: 30*15
        c: 40*35
    */

    //宣告變數
    struct rectangle a,b,c;

    a.height=20;
    a.width=10;

    b.height=30;
    b.width=15;

    c.height=40;
    c.width=35;

    printf("長方型a 長：%d 寬：%d\n", a.height, a.width);
    printf("長方型b 長：%d 寬：%d\n", b.height, b.width);
    printf("長方型c 長：%d 寬：%d\n", c.height, c.width);

    return 0;
}

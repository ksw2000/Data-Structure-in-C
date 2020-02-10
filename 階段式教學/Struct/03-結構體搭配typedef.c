#include<stdio.h>

/*
    另外也可以將
    struct rectangle
    這個型態換成更簡單一點的代表
    比如換成 rect
*/

struct rectangle{
    int height;
    int width;
};

// typedef (1) (2)
// (1):原先型態(可以很多空格) (2):這型態的新別名(只能有一個空格)
// 在讀取程式碼時也可以想成一旦看到 (2) 就再替代為 (1)
// 這只是 typedef 簡單的用法，還有一些比較高階的用法暫時不做介紹

typedef struct rectangle rect;

int main(){

    rect a,b,c;
    //可以想成把 rect 換成 struct rectangle
    //也就是這行在寫 struct rectangle a,b,c;
    //這個技巧很重要，因為 typedef 往往會有更為複雜的用法

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

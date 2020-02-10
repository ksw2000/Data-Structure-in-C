#include<stdio.h>

/*
    union 跟 struct 很像
    主要的區別在 union 內的成員只能選一個
    另外 union 的大小由裡面暫最大空間的那個決定

    詳情可參考
    http://gundambox.github.io/2015/10/30/C%E8%AA%9E%E8%A8%80-struct%E3%80%81union%E3%80%81enum/
*/

union u{
    char c;
    int n;
    float f;
};

int main(){
    union u foo;

    foo.c='c';
    printf("foo.c: %c\n", foo.c);
    printf("foo.n: %d\n", foo.n);     //無效(殘值)
    printf("foo.f: %e\n", foo.f);     //無效(殘值)

    printf("---------\n", foo.f);

    foo.n=87;
    printf("foo.c: %c\n", foo.c);     //無效(殘值)
    printf("foo.n: %d\n", foo.n);
    printf("foo.f: %e\n", foo.f);     //無效(殘值)

    printf("---------\n", foo.f);

    foo.f=6.626e-34;
    printf("foo.c: %c\n", foo.c);     //無效(殘值)
    printf("foo.n: %d\n", foo.n);     //無效(殘值)
    printf("foo.f: %e\n", foo.f);

    //%e 表示以科學記號方式印出 (因為 普朗克常數有點太小)

    return 0;
}

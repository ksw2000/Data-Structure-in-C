#include<stdio.h>

/*
    除了可以像前一個範例說在 int main()裡面以
    struct rectangle a,b,c;
    做宣告之外。在int main()外的全域區域也可以直接做宣告
*/

struct rectangle{
    int height;
    int width;
}a,b,c; //直接在結構體後做宣告

int main(){
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

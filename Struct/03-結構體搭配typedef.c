#include <stdio.h>

/*
    另外也可以將
    struct rectangle
    這個型態換成更簡單一點的代表
    比如換成 rect
*/

struct rectangle {
    int height;
    int width;
};

// typedef (1) (2)
// (1):原先型態(可以有空格) (2):別名(不能有空格)

typedef struct rectangle rect;

int main() {
    // You can see `rect` as struct rectangle
    rect a, b, c;

    a.height = 20;
    a.width = 10;

    b.height = 30;
    b.width = 15;

    c.height = 40;
    c.width = 35;

    printf("長方型a 長：%d 寬：%d\n", a.height, a.width);
    printf("長方型b 長：%d 寬：%d\n", b.height, b.width);
    printf("長方型c 長：%d 寬：%d\n", c.height, c.width);

    return 0;
}

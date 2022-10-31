#include <stdio.h>
#include <stdlib.h>

struct rectangle {
    int height;
    int width;
};

int main() {
    // 觀察下面的程式碼
    struct rectangle a;
    a.height = 20;
    a.width = 10;

    struct rectangle b;
    struct rectangle* pointerB;
    pointerB = &b;
    pointerB->height = 30;
    pointerB->width = 15;

    printf("長方型a 長：%d 寬：%d\n", a.height, a.width);
    printf("長方型b 長：%d 寬：%d\n", pointerB->height, pointerB->width);

    // 很明顯的可以發現如果是結構體的指標變數
    // 則在存取結構體內的成員時是採用 "->" 而不是 "."

    struct rectangle* c;
    // 用 malloc() 分配給 c 一塊記憶體
    c = malloc(sizeof(struct rectangle));
    c->height = 40;
    c->width = 35;

    printf("長方型c 長：%d 寬：%d\n", c->height, c->width);

    // -------------------------- 補充 --------------------------
    // 在 Go 語言的結構體(struct)中不管是結構體本身變數還是指標，一律用 "."
    // 來存取 在 PHP 的物件(object)中，一律用 "->" 來存取物件的內容 在 Java
    // 的類別(class)中，則是一律用 "." 來存取類別的內容
    // 基本上一般常見的語言都是用 "." 只是 PHP 的 "."
    // 被拿去做字串相加，所以只能用 "->"

    return 0;
}

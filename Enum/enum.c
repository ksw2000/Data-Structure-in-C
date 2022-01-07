#include <stdio.h>

// enum 的全稱為 enumeration 意思是列舉
// 他是 C 語言的一種自定義型態
// 是一組由識別字所代表的整數常數
// 比如我自訂義一個叫 boolean 的型態其中 true 代表 1 false 代表 0
// 又比如我自訂義一個叫 operand 再分別將 add, minus, times... 用整數表示

// 詳情可參考
// http://gundambox.github.io/2015/10/30/C%E8%AA%9E%E8%A8%80-struct%E3%80%81union%E3%80%81enum/

enum boolean { false = 0, true = 1 };
typedef enum boolean bool;

// 可以簡寫成
// enum bool{false, true};
// 在不指定數字的情況下就是由 0 開始編號

enum operand { add, minus, times, divide };
typedef enum operand op;

// 利用enum自定義的型態，也可以用來當函數的回傳型態
bool isEqual(int a, int b) {
    if (a == b) {
        return true;
    }
    return false;
}

op trans(char c) {
    switch (c) {
        case '+':
            return add;
        case '-':
            return minus;
        case '*':
            return times;
        case '/':
            return divide;
    }
}

int main() {
    printf("false:%d, true:%d\n", false, true);
    printf("add:%d ,minus:%d ,times:%d ,divide:%d ", add, minus, times, divide);

    return 0;
}

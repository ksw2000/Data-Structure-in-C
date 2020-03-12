/*
    本示範也是以 liked-list 實作 stack
    (學弟妹們可以用陣列實作 stack 即可，簡單效率高)

    另外，也可以參考 Fundmentals of data structures in c 2nd edition 第 131 頁 Figure 3.14
    或我也有放在本資料夾的 README.md 內
*/

#include<stdio.h>
#include<stdlib.h>

/*
    我們每次往計算式 pop 兩個數字，然後 pop 計算符號，算完後把數字 push 進去
    重複以上動作

    本試範程式只計算數字是個位數的算式，比如
    5 9 * 8 + ---> 5*9+8
    6 2 / 3 - 4 2 * + ---> 6/2-3 + 4*2
*/

struct s{
    int val;
    struct s* next;
};
typedef struct s* stack;

void push(stack* s, int val){
    stack new = malloc(sizeof(*new));
    new -> val = val;
    new -> next = *s;
    *s = new;
}

int pop(stack* s){
    stack temp = *s;
    int ret = temp -> val;
    *s = (*s)->next;
    free(temp);
    return ret;
}

enum p{
    plus, minus, times, divide, mod, eos, operand
};
typedef enum p precedence;

precedence getToken(char* expr, char* symbol, int* n){
    *symbol = expr[(*n)++];
    switch(*symbol){
        case '+':
            return plus;
        case '-':
            return minus;
        case '*':
            return times;
        case '/':
            return divide;
        case '%':
            return mod;
        case '\0':
            return eos;
        default:
            return operand;
    }
}

int eval(char* expr){
    stack stack_num = NULL;

    precedence token;
    int op1, op2;   // 暫時存取要算的兩個數字

    int n = 0;  // 讀取字串時的 index ，因為要從 0 開始讀所以預設為 0
    char symbol;    // 字串第 n 個字的字元，利用指標變數回傳(畢竟C的函數不能有兩個回傳值)
    token = getToken(expr, &symbol, &n);
    while(token != eos){
        if(token == operand){   // token 是數字時
            // '0' 可以視作 0 的 ascii 值 (即48)
            // 意思就是如果我得到 symbol='1' 那 symbol - '0' 可視為 '1' - '0' 即 49 - 28 = 1
            // 日後在處理「數字字元」轉換成「數字」時，可以多加利用這種計巧
            push(&stack_num, symbol - '0');
        }else{
            op2 = pop(&stack_num);
            op1 = pop(&stack_num);
            switch(token){
                case plus:
                    push(&stack_num, op1+op2);
                    break;
                case minus:
                    push(&stack_num, op1-op2);
                    break;
                case times:
                    push(&stack_num, op1*op2);
                    break;
                case divide:
                    push(&stack_num, op1/op2);
                    break;
                case mod:
                    push(&stack_num, op1%op2);
            }
        }
        token = getToken(expr, &symbol, &n);
    }

    return pop(&stack_num);   //最後堆疊內所剩的即為後序運算式的最終計算值
}

int main(){
    char equation1[] = "62/3-42*+";
    printf("%d\n", eval(equation1));    // 8

    char equation2[] = "59*8+";
    printf("%d\n", eval(equation2));    // 53

    system("pause");
    return 0;
}

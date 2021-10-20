/*
    本示範也是以 liked-list 實作 stack
    (學弟妹們可以用陣列實作 stack 即可，簡單效率高)

    找出以下迷宮路徑(任意一條即可)

 -> 0 0 0 0 0 0
    1 1 1 0 1 1
    1 0 0 0 0 1
    0 1 1 1 1 1
    1 0 0 0 0 1
    1 1 1 1 1 0
    1 0 0 0 0 1
    0 1 1 1 1 1
    1 0 0 0 0 0 -> END

    0 代表可走 1 代表不可走
    STEP1: 把起始點加入堆疊
    STEP2: 順時鐘尋找八個方向「上、上右、右、右下、下、左下、左、左上」
           只要找到其中一個方向不但不超出邊界且可以走就加入堆疊
           並且將其值改成 2 代表走過這裡，避免「重蹈覆轍」
           若是都找不到就退回上一步繼續找(因為走過的都被標為2，所以不會走回同一條)
    STEP3: 一直走直到走到終點，若是一直退回上一步，退到沒上一步可退(即pop不出東西)
           那就印出沒有路徑
*/

#include <stdio.h>
#include <stdlib.h>
#define MAZE_ROW 9
#define MAZE_COL 6

int maze[MAZE_ROW][MAZE_COL] = {
    {0, 0, 0, 0, 0, 0}, {1, 1, 1, 0, 1, 1}, {1, 0, 0, 0, 0, 1},
    {0, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 0},
    {1, 0, 0, 0, 0, 1}, {0, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0}};

typedef enum boolean { false, true } bool;

struct d {
    short int delta_row;
    short int delta_col;
};

// Stack
struct s {
    int row;
    int col;
    int direct;
    struct s* next;
};
typedef struct s* stack;

void push(stack* s, int row, int col, int direct);
stack pop(stack* s);
bool inBorder(int row, int col);

int main() {
    // STEP0: 設定八個方向
    struct d direct[] = {
        {-1, 0},  // ↑
        {-1, 1},  // ↗
        {0, 1},   // →
        {1, 1},   // ↘
        {1, 0},   // ↓
        {1, -1},  // ↙
        {0, -1},  // ←
        {-1, -1}  // ↖
    };

    stack path_stack = NULL;

    int now_row, now_col, i;
    now_row = 0;  //從(0,0)開始
    now_col = 0;  //從(0,0)開始

    int flag = 0;  // 0:繼續 1:找到迷宮的出路 2:迷宮沒有終點

    maze[0][0] = 2;  //(0,0)一定要走所以先留下痕跡
    for (; !flag;) {
        for (i = 0; i < 8; i++) {
            // 檢查是否超出邊界，沒有超出邊界再檢查是否為 0
            // printf("d(%d,%d)\n",now_row + direct[i].delta_row, now_col +
            // direct[i].delta_col);
            if (inBorder(now_row + direct[i].delta_row,
                         now_col + direct[i].delta_col)) {
                if (maze[now_row + direct[i].delta_row]
                        [now_col + direct[i].delta_col] == 0) {
                    //確定要走這條，將 now_row, now_col 改成新值
                    //(但位子是記錄舊的)
                    push(&path_stack, now_row, now_col, i);
                    now_row += direct[i].delta_row;
                    now_col += direct[i].delta_col;
                    maze[now_row][now_col] = 2;  //避免走到同一條(留下痕跡)
                    i = -1;  //讓下一個迴圈直接再從 0 開始

                    //檢查是否抵達終點
                    if (now_row == MAZE_ROW - 1 && now_col == MAZE_COL - 1) {
                        flag = 2;
                        break;  //為了連續退出兩個迴圈所以借助 flag 來達成
                    }
                }
            }
        }
        if (flag == 2)
            break;

        // 如果8個方向都沒中，程序會往這裡走
        stack pop_from_stack = pop(&path_stack);
        if (pop_from_stack) {
            now_row = pop_from_stack->row;
            now_col = pop_from_stack->col;
        } else {
            //如果pop出來什麼都沒有代表山窮水盡，找不到出口
            flag = 1;
        }
    }

    if (flag == 2) {
        printf("成功脫出，練習看看印出路徑吧！\n");
    } else if (flag == 1) {
        printf("脫出失敗，沒有路線可以脫出！\n");
    }

    system("pause");
    return 0;
}

void push(stack* s, int row, int col, int direct) {
    stack new = malloc(sizeof(*new));
    new->row = row;
    new->col = col;
    new->direct = direct;
    new->next = *s;
    *s = new;
}

stack pop(stack* s) {
    if (*s == NULL)
        return NULL;
    stack tmp = *s;
    *s = (*s)->next;
    return tmp;
}
/*
    這題如果用陣列實作堆疊會更為簡單
*/
bool inBorder(int row, int col) {
    if (row < 0 || row >= MAZE_ROW)
        return false;
    if (col < 0 || col >= MAZE_COL)
        return false;
    return true;
}

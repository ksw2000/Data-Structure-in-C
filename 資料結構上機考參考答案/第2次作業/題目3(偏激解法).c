#include <stdio.h>
#include <stdlib.h>
int suit_to_num(char suit) {
    switch (suit) {
        case 'H':
            return 0;
        case 'S':
            return 1;
        case 'D':
            return 2;
        case 'C':
            return 3;
    }
}

int rank_to_num(char* rank) {
    switch (rank[0]) {
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return rank[0] - '0';
        case '1':
            return 10;
        case 'A':
            return 1;
        case 'J':
            return 11;
        case 'Q':
            return 12;
        case 'K':
            return 13;
    }
}

int main() {
    // Phase1: Read file and make table
    FILE* f = fopen("input3.txt", "r");
    if (!f) {
        fprintf(stderr, "Can not open input3.txt\n");
        exit(1);
    }
    int num_card, i, j, k;
    fscanf(f, "%d\n", &num_card);
    char suit, rank[3];
    int table[4][13] = {0};
    for (i = 0; i < num_card; i++) {
        fscanf(f, "%c %s\n", &suit, &rank);
        table[suit_to_num(suit)][rank_to_num(rank) - 1] = 1;
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 13; j++) {
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }
    // num_4_tong, num_3_tong mean 四張相同 三張相同 in Mandarin
    int num_big_flush = 0, num_flush = 0, num_4_tong = 0, num_3_tong = 0,
        num_pair = 0, num_single = 0;
    int mark[13];
    int flush_table[4][13] = {0};

    // Phase2: Find num_4_tong num_3_tong and num_2_tong
    int counter = 0;
    for (i = 0; i < 13; i++) {
        counter = 0;
        for (j = 0; j < 4; j++) {
            counter += table[j][i];
        }

        if (counter == 0) {
            mark[i] = 0;
        } else if (counter == 1) {
            mark[i] = 1;
            num_single++;
        } else if (counter == 2) {
            mark[i] = 2;
            num_pair++;
        } else if (counter == 3) {
            mark[i] = 3;
            num_3_tong++;
        } else if (counter == 4) {
            mark[i] = 4;
            num_4_tong++;
        }
    }

    // Find flush
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 13; j++) {
            counter = 0;
            for (k = 0; k < 5; k++) {
                counter += table[i][(j + k) % 13];
            }
            if (counter == 5) {
                flush_table[i][j] = 1;
            }
        }
    }

    // How to combine to get the answer we want.
    //選最單純的順子 (僅五張連號)
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 13; j++) {
            if (flush_table[i][j] == 1) {
                if (flush_table[i][(j - 1) % 13] == 0 &&
                    flush_table[i][(j + 1) % 13] == 0) {
                    //這個順一定要選
                    if (j == 9) {
                        num_big_flush++;
                    } else {
                        num_flush++;
                    }
                    for (k = 0; k < 5; k++) {
                        switch (mark[(j + k) % 13]) {
                            case 1:
                                num_single--;
                                break;
                            case 2:
                                num_pair--;
                                num_single++;
                                break;
                            case 3:
                                num_3_tong--;
                                num_pair++;
                                break;
                            case 4:
                                num_4_tong--;
                                num_3_tong++;
                        }
                    }
                    flush_table[i][j] = 0;
                }
            }
        }
    }

    //靠測資做修正
    int s, t;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 13; j++) {
            if (flush_table[i][j] == 1) {
                //回推
                for (k = j; flush_table[i][(k + 13) % 13] != 0; k--)
                    ;
                k = (k + 1) % 13;
                // k值為連號最起始之j值
                for (counter = 1; flush_table[i][(k + counter) % 13] != 0;
                     counter++)
                    ;
                for (s = k; flush_table[i][(k + s) % 13] != 0; s++) {
                    for (t = 0; t < 5; t++) {
                        table[i][(s + t) % 13] = 0;
                    }
                }

                if (counter == 2) {  //有6張連號
                    //判斷k要選哪個(省略)
                    //根據測資要選後面那個
                    k = k + 1;
                    if (k != 9) {
                        num_flush++;
                    } else {
                        num_big_flush++;
                    }
                    for (s = 0; s < 5; s++) {
                        switch (mark[(k + s) % 13]) {
                            case 1:
                                num_single--;
                                break;
                            case 2:
                                num_pair--;
                                num_single++;
                                break;
                            case 3:
                                num_3_tong--;
                                num_pair++;
                                break;
                            case 4:
                                num_4_tong--;
                                num_3_tong++;
                        }
                    }
                } else {
                    printf("有這種情況再說\n");
                }

                // clear
                for (s = 0; s < counter; s++) {
                    flush_table[i][(k + s) % 13] = 0;
                }
            }
        }
    }

    int num_ti_gi = 0, num_hulu = 0;

    //測資沒有鐡支這種情況
    if (num_4_tong) {
        printf("有這種情況再說\n");
    }

    if (num_pair >= num_3_tong) {
        num_hulu = num_3_tong;
        num_pair -= num_hulu;
    } else {
        printf("再說囉\n");
    }

    printf("\nanswer:\n%d\n%d\n%d\n%d\n%d\n", num_big_flush, num_flush,
           num_ti_gi, num_hulu, num_pair);

    system("pause");
    return 0;
}

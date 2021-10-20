#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int min(int a, int b) {
    return (a > b) ? b : a;
}

void bubbleSort(int* arr, int len) {
    int i, j, tmp;
    for (i = 0; i < len; i++) {
        for (j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}
int main() {
    // Phase1: Read File
    FILE* f = fopen("input2.txt", "r");
    if (!f) {
        fprintf(stderr, "Cannot open input2.txt\n");
        exit(1);
    }

    int line = 0;
    int table[4][13] = {0};
    char buffer[64] = "";
    char* tmp;
    while (fgets(buffer, sizeof(buffer), f)) {
        printf("%s", buffer);
        // Skip the first character
        tmp = strtok(buffer, " ");
        for (tmp = strtok(NULL, " "); tmp; tmp = strtok(NULL, " ")) {
            if (line < 4) {
                table[line][rank_to_num(tmp) - 1] = 1;
            } else {
                table[line % 4][rank_to_num(tmp) - 1] = 2;
            }
        }
        line++;
    }

    // Phase2: Print two array for debugging
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 13; j++) {
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }

    // Phase3: Find royal flush
    int counterA, counterB;
    int change_how_many_cards_to_become_royal_flush[] = {99, 99, 99, 99};

    for (i = 0; i < 4; i++) {
        counterA = counterB = 0;
        for (j = 0; j < 5; j++) {
            counterA += (table[i][(9 + j) % 13] == 1);
            counterB += (table[i][(9 + j) % 13] == 2);
        }
        if (counterA + counterB == 5) {
            printf("[%d] has royal flush need to change %d times\n", i,
                   min(counterA, counterB));
            change_how_many_cards_to_become_royal_flush[i] =
                min(counterA, counterB);
        }
    }

    // Phase4: Get royal flush as many as possible
    bubbleSort(change_how_many_cards_to_become_royal_flush, 4);

    for (i = 0; i < 4; i++) {
        printf("%d ", change_how_many_cards_to_become_royal_flush[i]);
    }

    int counter = 0, num_royal_flush = 0;
    for (i = 0; i < 4; i++) {
        // Assume that we have sufficient single card to exchange with them.
        // Assume that we have sufficient single card to exchange with them.
        // Assume that we have sufficient single card to exchange with them.
        // It is important to need to repeat 3 times.
        if (counter + change_how_many_cards_to_become_royal_flush[i] <= 3) {
            counter += change_how_many_cards_to_become_royal_flush[i];
            num_royal_flush++;
        }
    }
    printf("answer:%d\n", num_royal_flush);

    // Phase5: Write to file
    f = fopen("output2.txt");
    fprintf(f, "%d", num_royal_flush);
    fclose(f);

    system("pause");
    return 0;
}

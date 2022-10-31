#include <stdio.h>

// in-place
// stable
// worst performance: O(n^2)
// best performance: O(n^2)
// average performance: O(n^2)

void insertionSort(int* list, int len) {
    int i, j;
    for (i = 1; i < len; i++) {
        for (j = i; j > 0 && list[j] < list[j - 1]; j--) {
            // swap list[j] and list[j-1]
            list[j] = list[j] ^ list[j - 1];
            list[j - 1] = list[j] ^ list[j - 1];
            list[j] = list[j] ^ list[j - 1];
        }
    }
}

void printList(int* list, int len) {
    int i = 0;
    for (i = 0; i < len; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

int main() {
    int list[] = {8, 7, 5, 6, 4, 2, 3, 1};
    int len = sizeof(list) / sizeof(list[0]);
    printf("list: ");
    // list: 8 7 5 6 4 2 3 1
    printList(list, len);
    insertionSort(list, len);
    printf("sorted list: ");
    // sorted list: 1 2 3 4 5 6 7 8
    printList(list, len);
    return 0;
}
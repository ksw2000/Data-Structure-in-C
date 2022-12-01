#include <stdio.h>
#include <stdlib.h>
#define cutoff 4

// not in-place
// stable
// worst performance: O(nlogn)
// best performance: O(nlogn)
// average performance: O(nlogn)

void insertionSort(int* list, int len) {
    int i, j;
    for (i = 1; i < len; i++) {
        for (j = i; j > 0 && list[j] < list[j - 1]; j--) {
            // swap list[j] with list[j-1]
            list[j] = list[j] ^ list[j - 1];
            list[j - 1] = list[j] ^ list[j - 1];
            list[j] = list[j] ^ list[j - 1];
        }
    }
}

void mergeSort(int* list, int len) {
    // when length is less than a cutoff (e.g. 4) use insertion sort.
    if (len < cutoff) {
        insertionSort(list, len);
        return;
    }

    // sort left and sort right
    int mid = len >> 1;
    // left part
    mergeSort(list, mid);
    // right part
    mergeSort(list + mid, len - mid);
    // merge
    int* tmpList = malloc(sizeof(int) * len);
    int i = 0, j = mid, k = 0;
    // i for traversing left part, j for traversing right part
    // k for temporary list
    while (i < mid && j < len) {
        tmpList[k++] = list[i] <= list[j] ? list[i++] : list[j++];
    }
    while (i < mid) {
        tmpList[k++] = list[i++];
    }
    while (j < len) {
        tmpList[k++] = list[j++];
    }
    // copy tmpList to list
    for (k = 0; k < len; k++) {
        list[k] = tmpList[k];
    }
    free(tmpList);
    return;
}

void printList(int* list, int len) {
    int i = 0;
    for (i = 0; i < len; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

int main() {
    int list[] = {8,  7,  5,  6,  4,  2,  3,  1, 18,
                  17, 15, 16, 14, 12, 13, 11, 9, 10};
    int len = sizeof(list) / sizeof(list[0]);
    printf("list: ");
    printList(list, len);
    // list: 8 7 5 6 4 2 3 1 18 17 15 16 14 12 13 11 9 10
    mergeSort(list, len);
    printf("sorted list: ");
    printList(list, len);
    // sorted list: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18
    return 0;
}
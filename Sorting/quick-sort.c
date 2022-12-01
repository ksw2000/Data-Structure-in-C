#include <stdio.h>
#define cutoff 4

// in-place
// not stable
// worst performance: O(n^2)
// best performance: O(nlogn)
// average performance: O(nlogn)

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

void quickSort(int* list, int len) {
    // when length is less than a cutoff (e.g. 4) use insertion sort.
    if (len < cutoff) {
        insertionSort(list, len);
        return;
    }

    // Select partition
    // In the real world, there are a lot of ways to choose partition.
    // I've just introduced the basic method, which is to select the last
    // element of an array
    int p = len - 1;  // p is the index of partition
    int s = -1;       // separator
    int i;
    for (i = 0; i < len - 1; i++) {
        if (list[i] <= list[p]) {
            s++;
            // swap list[s] with list[i]
            if (s != i) {
                list[s] = list[s] ^ list[i];
                list[i] = list[s] ^ list[i];
                list[s] = list[s] ^ list[i];
            }
        }
    }
    // Now,
    // list[s+1] is now greater than list[p]
    // list[s] is less or equal than list[p]

    // swap list[s+1] with list[p]
    s++;
    if (s != p) {
        list[s] = list[s] ^ list[p];
        list[p] = list[s] ^ list[p];
        list[s] = list[s] ^ list[p];
    }
    quickSort(list, s);
    quickSort(list + s + 1, len - s - 1);
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
    quickSort(list, len);
    printf("sorted list: ");
    printList(list, len);
    // sorted list: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18
    return 0;
}
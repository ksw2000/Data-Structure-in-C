#include <stdio.h>

struct element {
    int key;
    char* val;
};

// in-place
// NOT stable
// worst performance: O(n^2)
// best performance: O(n^2)
// average performance: O(n^2)

void selectionSort(struct element* list, int len) {
    int i, j, min;
    struct element tmp;
    // list[i] is the element should be replaced
    // list[j] is the smallest element in the left part of list
    for (i = 0; i < len - 1; i++) {
        min = i;
        for (j = i + 1; j < len; j++) {
            if (list[j].key < list[min].key) {
                min = j;
            }
        }
        // swap list[i] and list[min]
        tmp = list[i];
        list[i] = list[min];
        list[min] = tmp;
    }
}

void printList(struct element* list, int len) {
    int i = 0;
    for (i = 0; i < len; i++) {
        printf("(%d, %s)", list[i].key, list[i].val);
    }
    printf("\n");
}

int main() {
    struct element list[] = {{key : 40, val : "40 left"},
                             {key : 60, val : "60"},
                             {key : 40, val : "40 right"},
                             {key : 50, val : "50"},
                             {key : 20, val : "20"}};
    int len = sizeof list / sizeof list[0];
    printf("list: ");
    // list: (40, 40 left)(60, 60)(40, 40 right)(50, 50)(20, 20)
    printList(list, len);
    selectionSort(list, len);
    printf("sorted list: ");
    // sorted list: (20, 20)(40, 40 right)(40, 40 left)(50, 50)(60, 60)
    printList(list, len);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
void swap(int* a, int* b) {
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void inorder(int* heap, int index, int max_index, char* answer) {
    if (index <= max_index) {
        inorder(heap, index * 2, max_index, answer);
        printf("%d ", heap[index]);
        sprintf(answer, "%s%d ", answer, heap[index]);
        inorder(heap, index * 2 + 1, max_index, answer);
    }
}

void adjust(int* heap, int i, int num_nodes) {
    // Compare its left and right
    // Change the smaller one
    // If this node has two children, left and right
    if (i * 2 + 1 <= num_nodes) {
        if (heap[i * 2] > heap[i * 2 + 1]) {
            if (heap[i] > heap[i * 2 + 1]) {
                swap(&heap[i], &heap[i * 2 + 1]);
                adjust(heap, i * 2 + 1, num_nodes);
            }
        } else {
            if (heap[i] > heap[i * 2]) {
                swap(&heap[i], &heap[i * 2]);
                adjust(heap, i * 2, num_nodes);
            }
        }
        // If this node only has one child, left
    } else if (i * 2 <= num_nodes) {
        if (heap[i] > heap[i * 2]) {
            swap(&heap[i], &heap[i * 2]);
            adjust(heap, i * 2, num_nodes);
        }
    }
}
int main() {
    // Phase1: Read file and create heap
    FILE* f = fopen("input2.txt", "r");
    if (!f) {
        fprintf(stderr, "Cannot open input2.txt");
        exit(1);
    }
    int num_nodes = 0;
    char c;
    for (c = getc(f); c != '\n'; c = getc(f)) {
        if (c == ' ') {
            num_nodes++;
        }
    }
    num_nodes++;
    int* heap = malloc((num_nodes + 1) * sizeof(int));
    fclose(f);

    f = fopen("input2.txt", "r");
    int i, j;
    for (i = 0; i < num_nodes; i++) {
        fscanf(f, "%d", &heap[i + 1]);
    }
    fclose(f);

    printf("Before adjusting:\n");
    for (i = 0; i < num_nodes; i++) {
        printf("%d ", heap[i + 1]);
    }
    printf("\n");

    // Phase2: Adjust heap
    for (i = num_nodes; i > 0; i--) {
        adjust(heap, i, num_nodes);
    }

    printf("After adjusting:\n(Level order)\n");
    for (i = 0; i < num_nodes; i++) {
        printf("%d ", heap[i + 1]);
    }
    printf("\n");

    char answer[64] = "";
    printf("(In order)\n");
    inorder(heap, 1, num_nodes, answer);
    printf("\n");

    // Phase3: Write to file
    f = fopen("output2.txt", "w");
    fprintf(f, "%s", answer);
    fclose(f);

    system("pause");
    return 0;
}

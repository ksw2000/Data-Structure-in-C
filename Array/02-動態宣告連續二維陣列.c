#include <stdio.h>
#include <stdlib.h>

// Write a function called malloc2D() which allocates a 2d array.
// Minimize the number of calls to malloc() and make sure te memory is
// accessible by the notation array[i][j] Try allocate this as a contiguous
// block of memory, that space can be released by a single free() call.

int** allocate2D(int rows, int cols) {
    size_t overhead = sizeof(int*) * rows;
    void** array = malloc(overhead + sizeof(int) * rows * cols);
    int i;
    for (i = 0; i < rows; i++) {
        array[i] = array + overhead + i * cols;
    }
    return (int**)array;
}

void free2D(int** array) {
    free(array);
}

int main() {
    int rows = 9;
    int cols = 5;
    int** array2D = allocate2D(rows, cols);

    // TEST
    int i, j, count = 0;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            array2D[i][j] = count;
            count++;
        }
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%2d ", array2D[i][j]);
        }
        printf("\n");
    }

    free2D(array2D);

    return 0;
}

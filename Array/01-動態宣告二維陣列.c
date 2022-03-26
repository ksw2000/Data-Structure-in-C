#include <stdio.h>
#include <stdlib.h>

// How to simply allocate 2D array on runtime (in heap)?

int** allocate2D(int rows, int cols){
    // allocate memory for rows
    int** array2D = array2D = malloc(sizeof(int*) * rows);

    // allocate cols for each element in array2D
    int i;
    for (i = 0; i < rows; i++) {
        array2D[i] = malloc(sizeof(int) * cols);
    }
    return array2D;
}

void free2D(int** array2D, int rows){
    int i;
    for(i=0; i<rows; i++){
        free(array2D[i]);
    }
    free(array2D);
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

    free2D(array2D, rows);

    return 0;
}

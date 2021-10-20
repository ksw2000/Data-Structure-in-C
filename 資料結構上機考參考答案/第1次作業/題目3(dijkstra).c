#include <stdio.h>
#include <stdlib.h>
#define INFINITE 99999
struct q {
    int val;
    struct q* next;
};
typedef struct q* queue;
void enq(queue* q, int node) {
    queue new = malloc(sizeof(*new));
    new->val = node;
    new->next = NULL;
    if (*q == NULL) {
        *q = new;
    } else {
        queue current, previous;
        for (current = *q; current; current = current->next) {
            previous = current;
        }
        previous->next = new;
    }
}

int deq(queue* q) {
    queue tmp = (*q);
    int ans;
    if (*q) {
        ans = (*q)->val;
        (*q) = (*q)->next;
    } else {
        fprintf(stderr, "deq fail");
        exit(1);
    }

    free(tmp);
    return ans;
}

int main() {
    // Phase1: Read file
    FILE* f = fopen("input3.txt", "r");
    if (!f) {
        fprintf(stderr, "Cannot open input3.txt");
        exit(1);
    }
    int i, j, tmp, adj_matrix[7][7];
    char c;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
            fscanf(f, "%d", &tmp);
            adj_matrix[i][j] = (tmp == 0) ? INFINITE : tmp;
        }
    }

    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
            printf("%5d ", adj_matrix[i][j]);
        }
        printf("\n");
    }
    fclose(f);

    // Phase2: Dijkstra Algorithm
    int dist[7];
    for (i = 0; i < 7; i++) {
        dist[i] = INFINITE;
    }

    int vertex;
    int* visited = calloc(7, sizeof(int));
    queue traversal = NULL;

    enq(&traversal, 0);
    dist[0] = 0;
    visited[0] = 1;
    while (traversal) {
        vertex = deq(&traversal);
        for (i = 0; i < 7; i++) {
            if (visited[i] == 0 && adj_matrix[vertex][i] != INFINITE) {
                enq(&traversal, i);
                visited[i] = 1;
            }
            if (adj_matrix[vertex][i] != INFINITE) {
                if (adj_matrix[vertex][i] + dist[vertex] < dist[i]) {
                    dist[i] = adj_matrix[vertex][i] + dist[vertex];
                    printf("dist:");
                    for (j = 0; j < 7; j++) {
                        printf("%5d ", dist[j]);
                    }
                    printf("\n");
                }
            }
        }
    }

    printf("\n\n");
    for (i = 0; i < 7; i++) {
        printf("%d ", dist[i]);
    }
    printf("\n\n");

    printf("ans:%d\n", dist[6]);

    // Phase3: Write to file
    f = fopen("output3.txt", "w");
    fprintf(f, "%d", dist[6]);
    fclose(f);

    system("pause");
    return 0;
}

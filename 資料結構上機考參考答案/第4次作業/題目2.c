#include <stdio.h>
#include <stdlib.h>
#define INF 99999
struct l {
    int node;
    int weight;
    struct l* next;
};
typedef struct l* list;

void append(list* l, int node, int weight) {
    list current, previous, new;
    new = malloc(sizeof(*new));
    new->node = node;
    new->weight = weight;
    new->next = NULL;
    if (*l) {
        for (current = *l; current; current = current->next) {
            previous = current;
        }
        previous->next = new;
    } else {
        *l = new;
    }
}

int main() {
    // Phase1: Read file
    FILE* f = fopen("input2.txt", "r");
    char c;
    int num_node = 1;
    for (c = getc(f); c != '\n'; c = getc(f)) {
        if (c == ' ') {
            num_node++;
        }
    }
    fclose(f);

    list* adj_list = calloc(num_node, sizeof(list));
    int i, j, tmp;
    int* dist = calloc(num_node, sizeof(int));

    int num_path = 0, node_i, node_j;
    f = fopen("input2.txt", "r");
    for (i = 0; i < num_node; i++) {
        for (j = 0; j < num_node; j++) {
            fscanf(f, "%d", &tmp);
            if (tmp != 0) {
                append(&adj_list[i], j, tmp);
                num_path++;
            }
        }
    }
    fscanf(f, "%d", &node_i);
    fscanf(f, "%d", &node_j);
    node_i--;  // Because the graph start from 1 in ppt question
    node_j--;
    fclose(f);

    // Print adj_list
    list current;
    for (i = 0; i < num_node; i++) {
        printf("%d:", i);
        for (current = adj_list[i]; current; current = current->next) {
            printf("%2d(%2d) -> ", current->node, current->weight);
        }
        printf("NULL\n");
    }

    // Phase2: Bellman-Ford Algorithm
    for (i = 0; i < num_node; i++) {
        dist[i] = INF;
    }
    dist[node_i] = 0;

    for (i = 0; i < num_node; i++) {
        for (j = 0; j < num_node; j++) {
            // If 0~k is bigger than 0 via j to k, update
            for (current = adj_list[j]; current; current = current->next) {
                if (dist[current->node] > dist[j] + current->weight) {
                    dist[current->node] = dist[j] + current->weight;
                }
            }
        }
    }

    int error = 0, errorNode;
    for (j = 0; j < num_node; j++) {
        // If 0~k is bigger than 0 via j to k, update
        for (current = adj_list[j]; current; current = current->next) {
            if (dist[current->node] > dist[j] + current->weight) {
                error = 1;
                errorNode = current->node;
            }
        }
    }

    printf("dist:\n");
    for (i = 0; i < num_node; i++) {
        printf("%d ", dist[i]);
    }
    printf("\n");
    printf("ans: %d\n", (error == 0) ? dist[node_j] : errorNode + 1);

    // Phase3: Write file
    f = fopen("output2.txt", "w");
    fprintf(f, "%d", (error == 0) ? dist[node_j] : errorNode + 1);
    fclose(f);

    system("pause");
    return 0;
}

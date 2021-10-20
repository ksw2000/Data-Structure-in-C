#include <stdio.h>
#include <stdlib.h>
int main() {
    // Phase1: Read file
    FILE* f = fopen("input2.txt", "r");
    if (!f) {
        fprintf(stderr, "Cannot open input2.txt");
        exit(1);
    }

    int bounding, backup_weight, obj_weight[10];
    int i, j;
    fscanf(f, "%d %d", &bounding, &backup_weight);
    for (i = 0; i < 10; i++) {
        fscanf(f, "%d", &obj_weight[i]);
    }
    fclose(f);

    // Phase2: Exhaustion
    int max = 0, tmp_i, tmp_backup;
    for (i = 0; i < 1 << 10; i++) {
        tmp_i = i;
        tmp_backup = 0;
        for (j = 0; j < 10; j++) {
            if (tmp_i & 1) {
                tmp_backup += obj_weight[j];
                if (tmp_backup > bounding) {
                    break;
                }
            }
            tmp_i >>= 1;
        }
        if (tmp_backup <= bounding) {
            if (tmp_backup > max) {
                max = tmp_backup;
            }
        }
    }

    printf("%d\n", max + backup_weight);

    // Phase3: Write to file
    f = fopen("output2.txt", "w");
    fprintf(f, "%d", max + backup_weight);
    fclose(f);

    system("pause");
    return 0;
}

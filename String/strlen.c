#include <stdio.h>
#include <string.h>

int main() {
    printf("%d ", strlen("abc"));
    // 3

    printf("%d ", strlen("中文"));
    // 6 (UTF8) or 4 (Big5)

    return 0;
}

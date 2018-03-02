#include <stdio.h>

int main() {
    printf("press ctrl+c to exit.\n");
    for (;;) {
        int c = getchar();
        printf("%c=%d\n", c, c);
    }
    return 0;
}

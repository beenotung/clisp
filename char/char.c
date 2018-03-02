#include <stdio.h>

int main() {
    printf("press ctrl+c to exit.\n");
    for (;;) {
        printf("=======\n");
        int c = getchar();
        printf("|");
        switch (c) {
            case 27:
                printf(" ESC ");
                break;
            case ' ':
                printf("SPACE");
                break;
            case 9:
                printf(" TAB ");
                break;
            case 10:
                printf("ENTER");
                break;
            case 127:
                printf("<- BS");
                break;
            default:
                printf("  %c  ", c);
        }
        printf("|\n");
        printf("|-----|\n");
        printf("| %3d |\n", c);
    }
    return 0;
}

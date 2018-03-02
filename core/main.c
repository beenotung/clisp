#include <stdio.h>
#include <string.h>
#include <curses.h>

static char input[2048];
static int input_len = 0;
static int input_size = 2048;

int get_line() {
    input_len = 0;
    for (;;) {
        input_len++;
        if (input_len == input_size) {
            fprintf(stderr, "input buffer overflow\n");
            return 1;
        }
        char c = input[input_len] = getchar();
        if (c == '\n') {
            return 0;
        }
    }
}

int print_str(char input[], int len) {
    for (int i = 0; i < len; i++) {
        putc(input[i], stdout);
    }
    return 0;
}

int main(int argc, char **argv) {

    puts("clisp Version 0.0.1");
    puts("Press Ctrl+C to Exit\n");

    for (;;) {
        fputs("clisp> ", stdout);
        int return_code = get_line();
        if (return_code != 0) {
            return return_code;
        }
        printf("input_len=%d\n", input_len);
        printf("input_size=%d\n", input_size);
        printf("input=");
        print_str(input, input_len);
        printf("\n");
    }

    return 0;
}

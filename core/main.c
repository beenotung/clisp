#include <stdio.h>

static char input[2048];
static int input_cursor = 0;
static int input_len = 0;
static int input_size = 2048;

static char escape_sequence[3];

int init() {
    return 0;
}

int moveLeft() {
    printf("%c%c%c", 27, '[', 'D');
}

int moveRight() {
    printf("%c%c%c", 27, '[', 'C');
}

int clearEscape() {
    escape_sequence[0] = 0;
    escape_sequence[1] = 0;
    escape_sequence[2] = 0;
}

int fprint_str(FILE *IO, char input[], int len) {
    for (int i = 0; i < len; i++) {
        putc(input[i], IO);
    }
    return 0;
}

int print_str(char input[], int len) {
    return fprint_str(stdout, input, len);
}

int get_line() {
    clearEscape();
    input_cursor = 0;
    input_len = 0;
    inputLabel:
    for (;;) {
        char c = getchar();
        if (escape_sequence[0] == 0 && c == 27) {
            escape_sequence[0] = 27;
            continue;
        }
        if (escape_sequence[0] == 27) {
            if (escape_sequence[1] == 0) {
                escape_sequence[1] = c;
                continue;
            } else {
                escape_sequence[2] = c;
                if (escape_sequence[1] == '[') {
                    switch (c) {
                        case 'A':
                            /* up */
                        case 'B':
                            /* down */
                        case 'C':
                            /* right */
                            clearEscape();
                            if (input_cursor < input_len) {
                                input_cursor++;
                                moveRight();
                            }
                            goto inputLabel;
                        case 'D':
                            /* left */
                            clearEscape();
                            if (input_cursor > 0) {
                                input_cursor--;
                                moveLeft();
                            }
                            goto inputLabel;
                        default:
                            fprintf(stderr, "\nError: unknown escape sequence [%d,%d,%d]\n",
                                    escape_sequence[0],
                                    escape_sequence[1],
                                    escape_sequence[2]);
                            return 1;
                    }
                }
            }
        }
        if (c == '\n') {
            input[input_len] = '\0';
            printf("\n");
            return 0;
        }
        if (input_len == input_size) {
            fprintf(stderr, "\nError: input buffer overflow\n");
            return 1;
        }
        printf("%c", c);
        if (input_cursor == input_len) {
            /* append */
            fprintf(stderr, "append\n");
            input[input_cursor] = c;
        } else {
            /* insert */
            fprintf(stderr, "insert\n");
            fprintf(stderr, "input_cursor=%d\n", input_cursor);
            fprintf(stderr, "input_len=%d\n", input_len);
            fprintf(stderr, "input=");
            fprint_str(stderr, input, input_len);
            fprintf(stderr, "\n");
            for (int i = input_len; i > input_cursor; i--) {
                input[i] = input[i - 1];
            }
            input[input_cursor] = c;
            for (int i = input_cursor; i < input_len; i++) {
                printf("%c", input[i + 1]);
            }
            for (int i = input_cursor; i < input_len; i++) {
                moveLeft();
            }
        }
        input_cursor++;
        input_len++;
    }
}

int main(int argc, char **argv) {
    int code = init();
    if (code != 0) {
        return code;
    }

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

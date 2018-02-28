#include <stdio.h>

static char input[2048];

int main(int argc, char** argv) {

  puts("clisp Version 0.0.1");
  puts("Press Ctrl+C to Exit\n");

  for(;;){
    fputs("clisp> ",stdout);
    fgets(input, 2048, stdin);
    printf("input=%s",input);
  }

  return 0;
}

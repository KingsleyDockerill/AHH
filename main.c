#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"

int prompt() {
  int c, temp;
  char input[1000];
  printf(">");
  for(int i = 0; (c = getchar()) != '\n'; i++) {
    input[i] = c;
    temp = i;
  }
  input[temp + 1] = '\0';
  token* toks;
  toks = generate(input);
  for(int i = 0; toks[i].name != NULL; i++) {
    if(toks[i].type == 's') {
      printf("%s: %s, ", toks[i].name, toks[i].value.s);
    }
    else if(toks[i].type == 'i') {
      printf("%s: %d, ", toks[i].name, toks[i].value.i);
    }
  }
  // This line will erase any evidence of the tokens ever existing. Without the program will store the results forever
  for(int i = 0; toks[i].name != NULL; i++) {
    toks[i].name = NULL;
    toks[i].value.s = NULL;
    toks[i].type = NULL;
  }
  puts("");
  return 0;
}

int main(int argc, char* argv[]) {
  while (1) {
    if(prompt()) {
      break;
    }
  }
  return 0;
}
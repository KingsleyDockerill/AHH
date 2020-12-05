#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"

int prompt() {
  int c, temp;
  char input[1000];
  for(int i = 0; (c = getchar()) != '\n'; i++) {
    input[i] = c;
    temp = i;
  }
  input[temp + 1] = '\0';
  token* toks;
  toks = generate(input);
  for(int i = 0; toks[i].name != NULL; i++) {
    printf("%s: %s, ", toks[i].name, toks[i].value.s);
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
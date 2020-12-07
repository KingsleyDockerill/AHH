#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "builtins.h"

int prompt() {
  int temp;
  char input[1000], c;
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
      printf("%s: %lld, ", toks[i].name, toks[i].value.i);
    }
  }
  puts("");
  // Clear the tokens
  for(int i = 0; toks[i].name != NULL; i++) {
    toks[i].name = NULL;
    toks[i].value.s = NULL;
    toks[i].value.i = NULL;
    toks[i].type = NULL;
  }
  return 0;
}

int main(int argc, char* argv[]) {
  printf("%s", read("parser.h", "r"));
  while (1) {
    if(prompt()) {
      break;
    }
  }
  return 0;
}
// https://stackoverflow.com/questions/65130472/how-do-i-make-a-variable-in-a-struct-equal-to-any-value-without-a-warning-c
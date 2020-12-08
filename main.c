#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "error.h"
// I use this for testing a lot so I'm gonn a leave this here as a comment
#include "builtins.h"

int prompt() {
  int temp;
  char input[10000], c;
  printf(">");
  for(int i = 0; (c = getchar()) != '\n'; i++) {
    if(i == 10000) {
      puts(raise("", "Input cannot exede 9999 characters in length", 1));
      return 0;
    }
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
  printf("%d", factor(toks));
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
  while (1) {
    if(prompt()) {
      break;
    }
  }
  return 0;
}
// https://stackoverflow.com/questions/65130472/how-do-i-make-a-variable-in-a-struct-equal-to-any-value-without-a-warning-c
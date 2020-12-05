#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"

char* stolower(char* string) {
  char a[1000];
  for(int i; string[i] != '\0'; i++) {
    if((int)string[i] >= 65 && (int)string[i] <= 90 && string[i] != '\0') {
      i = (int) i;
      a[i] = (char) i + 32;
    }
    else {
      a[i] = string[i];
    }
  }
  return a;
}

int prompt() {
  int c, temp;
  char input[1000];
  for(int i = 0; (c = getchar()) != '\n'; i++) {
    input[i] = c;
    temp = i;
  }
  input[temp + 1] = '\0';
  char* tempin;
  tempin = input;
  tempin = stolower(tempin);
  if(strcmp(tempin, "end") == 0) {
    return 1;
  }
  token* toks;
  toks = generate(input);
  for(int i = 0; toks[i].name != NULL; i++) {
    printf("%s: %s, ", toks[i].name, toks[i].value.s);
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
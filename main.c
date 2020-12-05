#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"

void stolower(char* string) {
  for(int i; string[i] != '\0'; i++) {
    if((int)string[i] >= 65 && (int)string[i] <= 90 && string[i] != '\0') {
      string[i] = (char) i + 32;
    }
  }
}

int main(void) {
  while(1) {
    int c, temp;
    char input[1000];
    for(int i = 0; (c = getchar()) != '\n'; i++) {
      input[i] = c;
      temp = i;
    }
    input[temp + 1] = '\0';
    char* tempin;
    tempin = input;
    stolower(tempin);
    if(!strcmp(tempin, "end")) {
      break;
    }
    token* toks;
    toks = generate(input);
    for(int i = 0; toks[i].name != NULL; i++) {
      printf("%s: %s", toks[i].name, toks[i].value.s);
    }
    puts("");
  }
  return 0;
}
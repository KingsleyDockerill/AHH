#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"
#include "error.h"
#include "builtins.h"

#define OS name()

const char* get_tok_name(enum tokentypes tok) 
{
   switch (tok) 
   {
      case add: return "add";
      case sub: return "sub";
      case mul: return "mul";
      case div_: return "div";
      case num: return "num";
      case lparen: return "lparen";
      case rparen: return "rparen";
      case eof: return "eof";
      default: return "???";
   }
}

int prompt() {
  int temp;
  char input[10000], c;
  printf(">");
  for(int i = 0; (c = getchar()) != '\n'; i++) {
    if(i == 10000) {
      puts(raise("", "Input cannot exceed 9999 characters in length", 1));
      return 0;
    }
    input[i] = c;
    temp = i;
  }
  input[temp + 1] = '\0';
  token* toks = generate(input);
  node parsed = parse(toks);
  printf("%lld\n", interpret(parsed).value.i);
  // Clear the tokens
  for(int i = 0; toks[i].null_ != NULL; i++) {
    toks[i].name = eof;
    toks[i].value.s = NULL;
    toks[i].value.i = 0;
    toks[i].value.c = '\0';
    toks[i].type = '\0';
  }
  return 0;
}

int main(int argc, char* argv[]) {
  if(argc > 1) {
    char* input;
    input = read(argv[1], "r");
    token* toks = generate(input);
    node parsed = parse(toks);
    printf("%lld\n", interpret(parsed).value.i);
    // Clear the tokens
    for(int i = 0; toks[i].null_ != NULL; i++) {
      toks[i].name = eof;
      toks[i].value.s = NULL;
      toks[i].value.i = 0;
      toks[i].value.c = '\0';
      toks[i].type = '\0';
    }
    exit(0);
  }
  while (1) {
    if(prompt()) {
      break;
    }
  }
  return 0;
}
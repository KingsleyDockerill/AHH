#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "error.h"
// I use this for testing a lot so I'm gonna leave this here as a comment
// #include "builtins.h"

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
  token* toks;
  toks = generate(input);
  node parsed = parse(toks);
  printf("%s\n", parsed.name);
  // Clear the tokens
  for(int i = 0; toks[i].null_ != NULL; i++) {
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
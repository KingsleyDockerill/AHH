#include <stdio.h>

#ifndef lex
  #define lex
  typedef struct {
      char* name;
      char type;
      union {
          long long i;
          char c;
          char *s;
          float f;
          double d;
      } value;
  } token;
  token* generate(char* input);
  short _in(char a, char* b);
#endif
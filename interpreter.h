#ifndef interpreter___
  #include "parser.h"
  #define interpreter___
  typedef struct {
    char* name;
    char type;
    union {
      long long i;
      char c;
      char *s;
      double f;
    } value;
    char* null_;
  } var;
  var interpret(node a);
#endif
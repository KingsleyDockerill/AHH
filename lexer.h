#ifndef lex
  #define lex
  enum tokentypes {
    add,
    sub,
    mul,
    div_,
    num
  };
  typedef struct {
      enum tokentypes name;
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
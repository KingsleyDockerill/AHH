#ifndef lex
  #define lex
  enum tokentypes {
    builtin,
    add,
    sub,
    mul,
    div_,
    num,
    and,
    or,
    xor,
    lparen,
    rparen,
    eol,
    eof
  };
  typedef struct {
      enum tokentypes name;
      char type;
      union {
          long long i;
          char c;
          char *s;
          double f;
      } value;
      char* null_;
  } token;
  token* generate(char* input);
  short _in(char a, char* b);
#endif
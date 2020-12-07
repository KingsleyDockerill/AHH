#include "lexer.h"
#include "error.h"

short _in(char a, char* b) {
  for(int i = 0; b[i] != '\0'; i++) {
    if(b[i] == a) {
      return 1;
    }
  }
  return 0;
}

token* generate(char* input) {
  token toks[10000];
  static char* digits = "0123456789";
  int pos = 0;
  for(int i = 0; input[i] != '\0'; i++) {
    token temp;
    switch(input[i]) {
      case '+' :
        printf("");
        token temp;
        temp.name = "add";
        temp.type = 's';
        temp.value.s = "+";
        toks[pos] = temp;
        ++pos;
        break;
      case '-' :
        printf("");
        temp.name = "sub";
        temp.type = 's';
        temp.value.s = "-";
        toks[pos] = temp;
        ++pos;
        break;
      case '*' :
        printf("");
        temp.name = "mul";
        temp.type = 's';
        temp.value.s = "*";
        toks[pos] = temp;
        ++pos;
        break;
      case '/' :
        printf("");
        temp.name = "div";
        temp.type = 's';
        temp.value.s = "/";
        toks[pos] = temp;
        ++pos;
        break;
      default :
        if(_in(input[i], "0123456789")){
          char a[102];
          int numpos = 0, tempi = 0;
          while(_in(input[i], "0123456789")) {
            a[numpos] = input[i];
            i++;
            numpos++;
            tempi = numpos;
          }
          // Why do I do this? Because in the above for loop i++ is executed too many times
          i = i - 1;
          a[tempi] = '\0';
          temp.name = "num";
          temp.type = 'i';
          int b;
          sscanf(a, "%d", &b);
          temp.value.i = b;
          toks[pos] = temp;
          pos++;
          break;
        }
        raise("Lexer Error", "Found illegal token", 0);
    }
  }
  return toks;
}
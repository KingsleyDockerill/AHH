#include "lexer.h"
#include "error.h"
#include <stdio.h>

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
        temp.name = add;
        temp.type = 's';
        temp.value.s = "+";
        toks[pos] = temp;
        toks[pos].null_ = " ";
        pos++;
        break;
      case '-' :
        printf("");
        temp.name = sub;
        temp.type = 's';
        temp.value.s = "-";
        toks[pos] = temp;
        toks[pos].null_ = " ";
        pos++;
        break;
      case '*' :
        printf("");
        temp.name = mul;
        temp.type = 's';
        temp.value.s = "*";
        toks[pos] = temp;
        toks[pos].null_ = " ";
        pos++;
        break;
      case '/' :
        printf("");
        temp.name = div_;
        temp.type = 's';
        temp.value.s = "/";
        toks[pos] = temp;
        toks[pos].null_ = " ";
        pos++;
        break;
      case '&' :
        printf("");
        temp.name = and;
        temp.type = 's';
        temp.value.s = "&";
        toks[pos] = temp;
        toks[pos].null_ = " ";
        pos++;
        break;
      case '|' :
        printf("");
        temp.name = or;
        temp.type = 's';
        temp.value.s = "|";
        toks[pos] = temp;
        toks[pos].null_ = " ";
        pos++;
        break;
      case '^' :
        printf("");
        temp.name = xor;
        temp.type = 's';
        temp.value.s = "^";
        toks[pos] = temp;
        toks[pos].null_ = " ";
        pos++;
        break;
      case '=' :
        printf("");
        temp.name = equal;
        temp.type = 's';
        temp.value.s = "=";
        toks[pos] = temp;
        toks[pos].null_ = " ";
        pos++;
        break;
      case '$' :
        printf("");
        temp.name = equal;
        temp.type = 's';
        temp.value.s = "=";
        toks[pos] = temp;
        toks[pos].null_ = " ";
        pos++;
        break;
      case '\n' :
        printf("");
        temp.name = eol;
        toks[pos] = temp;
        toks[pos].null_ = " ";
        pos++;
      case '\'' :
        printf("");
        i++;
        temp.name = char_;
        temp.type = 'c';
        if(input[i] == '\\') {
          i++;
          if(input[i] == 'n') {
            temp.value.c = '\n';
          }
          else if(input[i] == 't') {
            temp.value.c = '\t';
          }
          else if(input[i] == 'b') {
            temp.value.c = '\b';
          }
          else {
            raise("LexerError", "Char has no closing '", 0);
          }
        }
        else {
          temp.value.c = input[i];
        }
        toks[pos] = temp;
        toks[pos].null_ = " ";
        i++;
        if(input[i] != '\'') {
          raise("LexerError", "Char has no closing '", 0);
        }
        pos++;
        break;
      // Parentheses are a wip
      case '(' :
        printf("");
        temp.name = lparen;
        temp.type = 's';
        temp.value.s = "(";
        toks[pos] = temp;
        toks[pos].null_ = " ";
        pos++;
        break;
      case ')' :
        printf("");
        temp.name = rparen;
        temp.type = 's';
        temp.value.s = ")";
        toks[pos] = temp;
        toks[pos].null_ = " ";
        pos++;
        break;
      case ' ' :
        break;
      case '\t' :
        break;
      default :
        if(_in(input[i], "0123456789")){
          char a[1000];
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
          temp.name = num;
          temp.type = 'i';
          int b;
          sscanf(a, "%d", &b);
          temp.value.i = b;
          toks[pos] = temp;
          toks[pos].null_ = " ";
          pos++;
          break;
        }
        else {
          char a[1000];
          int pos_ = 0, tempi = 0;
          while(!_in(input[i], " \t(")) {
            a[pos_] = input[i];
            i++;
            pos_++;
            tempi = pos_;
          }
          i = i - 1;
          a[tempi] = '\0';
          temp.name = builtin;
          temp.type = 's';
          temp.value.s = a;
          temp.null_ = " ";
          toks[pos] = temp;
          pos++;
          break;
        }
      }
  }
  toks[pos].name = eof;
  return toks;
}
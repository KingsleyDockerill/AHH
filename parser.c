#include "parser.h"
#include "lexer.h"
#include "error.h"
// This is for malloc
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char* get_tok_name(enum tokentypes tok) 
{
   switch (tok) 
   {
      case add: return "add";
      case sub: return "sub";
      case mul: return "mul";
      case div_: return "div";
      case and: return "and";
      case or: return "or";
      case num: return "num";
      case builtin: return "builtin";
      case lparen: return "lparen";
      case rparen: return "rparen";
      case eof: return "eof";
      default: return "???";
   }
}

node parse_;
token toks[10000];
int tokpos = 0;

// These functions are used for assigning the void pointer in the node struct
void *copy_node(node arg)
{
  node *mem = malloc(sizeof(*mem));
  if(mem)
    *mem = arg;
  return mem;
}

long long* copy_int(long long arg)
{
  long long *mem = malloc(sizeof(*mem));
  if(mem)
    *mem = arg;
  return mem;
}

char* copy_char(char arg)
{
  char *mem = malloc(sizeof(*mem));
  if(mem)
    *mem = arg;
  return mem;
}

void* copy_string(const char *str)
{
  char *mem = malloc(sizeof(*mem * (strlen( str ) + 1)));
  if (mem)
    strcpy(mem, str);
  return mem;
}

// This specifies how many arguments builtins take. Basically
// print : 1
// input : 1
// And so on
void init_builtins() {
}

node factor() {
  if(toks[tokpos].name == num) {
    node new_node;
    new_node.name = "num";
    new_node.nodes[0] = copy_int(toks[tokpos].value.i);
    tokpos++;
    return new_node;
  }
  // For these tokpos goes too far, so I have to do tokpos - 1
  else if(toks[tokpos].name == add) {
    node new_node;
    new_node.name = "num";
    new_node.nodes[0] = copy_int(+toks[tokpos + 1].value.i);
    tokpos += 2;
    return new_node;
  }
  else if(toks[tokpos].name == sub) {
    node new_node;
    new_node.name = "num";
    new_node.nodes[0] = copy_int(-toks[tokpos + 1].value.i);
    tokpos += 2;
    return new_node;
  }
  else if(toks[tokpos].name == char_) {
    node b;
    b.name = "char";
    b.nodes[0] = copy_char(toks[tokpos].value.c);
    return b;
  }
  else if(toks[tokpos].name == eof) {
    node b;
    return b;
  }
  else {
    raise("SyntaxError", "Unexpected token found while parsing", 0);
  }
  node a;
  return a;
}

node varaccess() {
  node a = factor();
  if(toks[tokpos].name == dollar) {
    a.name = "varaccessnode";
    a.nodes[0] = copy_string(toks[tokpos].value.s);
  }
  return a;
}

node bitops() {
  node a = varaccess();
  while(toks[tokpos].null_ != NULL && (toks[tokpos].name == and || toks[tokpos].name == or)) {
    if(toks[tokpos].name == and) {
      node b;
      b.name = "andnode";
      b.nodes[0] = copy_node(a);
      tokpos++;
      b.nodes[1] = copy_node(factor());
      a = b;
    }
    else if(toks[tokpos].name == or) {
      node b;
      b.name = "ornode";
      b.nodes[0] = copy_node(a);
      tokpos++;
      b.nodes[1] = copy_node(factor());
      a = b;
    }
    else if(toks[tokpos].name == xor) {
      node b;
      b.name = "xornode";
      b.nodes[0] = copy_node(a);
      tokpos++;
      b.nodes[1] = copy_node(factor());
      a = b;
    }
  }
  return a;
}

node muldiv() {
  node a = bitops();
  while(toks[tokpos].null_ != NULL && (toks[tokpos].name == mul || toks[tokpos].name == div_)) {
    if(toks[tokpos].name == mul) {
      node b;
      b.name = "mulnode";
      b.nodes[0] = copy_node(a);
      tokpos++;
      b.nodes[1] = copy_node(factor());
      a = b;
    }
    else if(toks[tokpos].name == div_) {
      node b;
      b.name = "divnode";
      b.nodes[0] = copy_node(a);
      tokpos++;
      b.nodes[1] = copy_node(factor());
      a = b;
    }
  }
  return a;
}

node expr() {
  node a = muldiv();
  while(toks[tokpos].null_ != NULL && (toks[tokpos].name == add || toks[tokpos].name == sub || toks[tokpos].name == lparen)) {
    if(toks[tokpos].name == add) {
      node b;
      b.name = "addnode";
      b.nodes[0] = copy_node(a);
      tokpos++;
      b.nodes[1] = copy_node(muldiv());
      a = b;
    }
    else if(toks[tokpos].name == sub) {
      node b;
      b.name = "subnode";
      b.nodes[0] = copy_node(a);
      tokpos++;
      b.nodes[1] = copy_node(muldiv());
      a = b;
    }
    tokpos++;
  }
  tokpos++;
  return a;
}

node builtins() {
  token builtinname = toks[tokpos];
  node a;
  tokpos++;
  if(toks[tokpos].name == builtin) {
    a = builtins();
  }
  else if(toks[tokpos].name == equal) {}
  else {
    a = expr();
  }
  if(builtinname.name == builtin) {
    if(toks[tokpos].name == equal) {
      tokpos++;
      node b;
      b.name = "varassignnode";
      b.nodes[0] = copy_string(builtinname.value.s);
      b.nodes[1] = copy_node(builtins());
      tokpos++;
      a = b;
    }
    else {
      node b;
      b.name = "functionnode";
      b.nodes[0] = copy_node(a);
      tokpos++;
      a = b;
    }
  }
  else if(builtinname.name == char_) {
    tokpos++;
    node b;
    b.name = "char";
    putchar(toks[tokpos].value.c);
    puts("");
    b.nodes[0] = copy_char(builtinname.value.c);
    a = b;
  }
  return a;
}

node parse(token tokens[]) {
  // This makes the tokens global so any function can access them
  for(int i = 0; tokens[i].null_ != NULL; i++) {
    toks[i] = tokens[i];
  }
  parse_ = builtins();
  tokpos = 0;
  return parse_;
}
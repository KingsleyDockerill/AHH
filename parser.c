#include "parser.h"
#include "lexer.h"
#include "error.h"
// This is for malloc
#include <stdlib.h>

node parse_;
token* toks;
int tokpos = 0;

// These functions are used for assigning the void pointer in the node struct
void *copy_node(node arg)
{
  node *mem = malloc(sizeof(*mem));
  if(mem)
    *mem = arg;
  return mem;
}

int *copy_int(int arg)
{
  int *mem = malloc(sizeof(*mem));
  if(mem)
    *mem = arg;
  return mem;
}

node factor(token tokens[]) {
  toks = tokens;
  if(toks[tokpos].name == num) {
    node new_node;
    new_node.name = "num";
    new_node.nodes[0] = copy_int(toks[tokpos].value.i);
    return new_node;
  }
  else if(toks[tokpos].name == add) {
    node new_node;
    new_node.name = "num";
    new_node.nodes[0] = copy_int(+toks[tokpos].value.i);
    return new_node;
  }
  else if(toks[tokpos].name == sub) {
    node new_node;
    new_node.name = "num";
    new_node.nodes[0] = copy_int(-toks[tokpos].value.i);
    return new_node;
  }
  else {
    raise("SyntaxError", "Unexpected token found while parsing", 0);
  }
  node a;
  return a;
}

node muldiv () {
  node a = factor(NULL);
  if(toks[tokpos].name == add) {
    node b;
    b.name = "addnode";
    b.nodes[0] = copy_node(a);
    a.nodes[1] = copy_node(factor(NULL));
  }
  return a;
}

node expr() {
  node num = muldiv();
  node a;
  return a;
}

node parse(token tokens[]) {
  toks = tokens;
  parse_ = expr();
  return parse_;
}
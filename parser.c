#include "parser.h"
#include "lexer.h"
#include "error.h"
// This is for malloc
#include <stdlib.h>
#include <stdio.h>

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
  else {
    raise("SyntaxError", "Unexpected token found while parsing", 0);
  }
  node a;
  return a;
}

node muldiv () {
  node a = factor();
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
  tokpos = 0;
  return a;
}

node parse(token tokens[]) {
  // This makes the tokens global so any function can access them
  for(int i = 0; tokens[i].null_ != NULL; i++) {
    toks[i] = tokens[i];
  }
  parse_ = expr();
  return parse_;
}
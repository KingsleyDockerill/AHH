#include "parser.h"
#include "lexer.h"
// This is for malloc
#include <stdlib.h>
#include <string.h>

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

node factor() {
  if(strcmp(toks[tokpos].name, "num") == 0) {
    node new_node;
    new_node.name = "num";
    new_node.nodes[0] = copy_int(toks[tokpos].value.i);
    printf("%d", new_node.nodes[0]);
    return new_node;
  }
  node a;
  return a;
}

node muldiv () {
  node a= factor();
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
#include "lexer.h"
#ifndef parserdeclared
#define parserdeclared
typedef struct {
  char* name;
  void* nodes[10000];
} node;
void* copy_node(node arg);
void init_builtins();
long long* copy_int(long long arg);
node parse(token tokens[]);
node expr();
node muldiv();
node factor();
#endif
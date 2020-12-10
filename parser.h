#include "lexer.h"
typedef struct {
  char* name;
  void* nodes[1000];
} node;
void* copy_node(node arg);
long long* copy_int(long long arg);
node parse(token tokens[]);
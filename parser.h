typedef struct {
  char* name;
  void* nodes[1000];
} node;
void* copy_node(node arg);
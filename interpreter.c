#include "interpreter.h"
#include "parser.h"
#include "error.h"
#include "builtins.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// This represents the size of the malloc your variables are stored in. It can be changed using -varmalloc 50 for the max amount of variables.
int varmalloc = 10000;

var* global_vars;

var interpret(node a) {
  // Since you can't set a global variable equal to a function, I have to do this.
  if(global_vars == NULL) {
    global_vars = (var*) malloc(varmalloc);
    if(global_vars == NULL) {
      raise("MallocError", "Free up memory or get a bigger RAM", 0);
    }
  }
  if(strcmp(a.name, "num") == 0) {
    long long num = *((long long*) a.nodes[0]);
    var newvar;
    newvar.name = "integer";
    newvar.value.i = num;
    newvar.type = 'i';
    newvar.null_ = " ";
    return newvar;
  }
  else if(strcmp(a.name, "addnode") == 0) {
    long long num1 = interpret(*((node*) a.nodes[0])).value.i;
    long long num2 = interpret(*((node*) a.nodes[1])).value.i;
    var newvar;
    newvar.name = "addition";
    newvar.value.i = num1 + num2;
    newvar.type = 'i';
    newvar.null_ = " ";
    return newvar;
  }
  else if(strcmp(a.name, "subnode") == 0) {
    long long num1 = interpret(*((node*) a.nodes[0])).value.i;
    long long num2 = interpret(*((node*) a.nodes[1])).value.i;
    var newvar;
    newvar.name = "subtraction";
    newvar.value.i = num1 - num2;
    newvar.type = 'i';
    newvar.null_ = " ";
    return newvar;
  }
  else if(strcmp(a.name, "mulnode") == 0) {
    long long num1 = interpret(*((node*) a.nodes[0])).value.i;
    long long num2 = interpret(*((node*) a.nodes[1])).value.i;
    var newvar;
    newvar.name = "multiplication";
    newvar.value.i = num1 * num2;
    newvar.type = 'i';
    newvar.null_ = " ";
    return newvar;
  }
  else if(strcmp(a.name, "divnode") == 0) {
    long long num1 = interpret(*((node*) a.nodes[0])).value.i;
    long long num2 = interpret(*((node*) a.nodes[1])).value.i;
    if(num2 != 0) {
      var newvar;
      newvar.name = "addition";
      newvar.value.i = num1 + num2;
      newvar.type = 'i';
      newvar.null_ = " ";
      return newvar;
    }
    else {
      printf("%s:\n%s\n", "ZeroDivisionError", "Returning 0");
      var newvar;
      newvar.value.i = 0;
      newvar.type = 'i';
      return newvar;
    }
  }
  else if(strcmp(a.name, "andnode") == 0) {
    long long num1 = interpret(*((node*) a.nodes[0])).value.i;
    long long num2 = interpret(*((node*) a.nodes[1])).value.i;
    var newvar;
    newvar.name = "and";
    newvar.value.i = num1 & num2;
    newvar.type = 'i';
    newvar.null_ = " ";
    return newvar;
  }
  else if(strcmp(a.name, "ornode") == 0) {
    long long num1 = interpret(*((node*) a.nodes[0])).value.i;
    long long num2 = interpret(*((node*) a.nodes[1])).value.i;
    var newvar;
    newvar.name = "or";
    newvar.value.i = num1 | num2;
    newvar.null_ = " ";
    return newvar;
  }
  else if(strcmp(a.name, "xornode") == 0) {
    long long num1 = interpret(*((node*) a.nodes[0])).value.i;
    long long num2 = interpret(*((node*) a.nodes[1])).value.i;
    var newvar;
    newvar.name = "xor";
    newvar.value.i = num1 ^ num2;
    newvar.null_ = " ";
  }
  else if(strcmp(a.name, "functionnode") == 0) {
    var toprint = interpret(*((node*) a.nodes[0]));
    print(toprint);
    var nullnode;
    nullnode.type = 's';
    nullnode.name = NULL;
    return nullnode;
  }
  else if(strcmp(a.name, "varassignnode") == 0) {
    char* name = *((char**) a.nodes[0]);
    var toassign = interpret(*((node*) a.nodes[1]));
    int i;
    // Get the most recently freed piece of memory
    for(i = 0; ((var*)global_vars + i)->null_ != NULL; i++){ }
    *((var*)global_vars + i) = toassign;
    var nullnode;
    nullnode.type = 's';
    nullnode.name = NULL;
    return nullnode;
  }
  else if(strcmp(a.name, "varaccessnode") == 0) {
    int i;
    char* name = *((char**) a.nodes[0]);
    for(i = 0; strcmp(((var*)global_vars + i)->name, name) != 0 && ((var*)global_vars + i)->null_ != NULL; i++) { }
    return *((var*)global_vars + i);
  }
  else if(strcmp(a.name, "char") == 0) {
    var chr;
    chr.type = 'c';
    chr.value.c = *((char*) a.nodes[0]);
    return chr;
  }
  else {
    raise("NodeError", "Unexpected node", 0);
  }
}
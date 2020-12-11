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
    newvar.null_ = " ";
    return newvar;
  }
  else if(strcmp(a.name, "addnode") == 0) {
    long long num1 = interpret(*((node*) a.nodes[0])).value.i;
    long long num2 = interpret(*((node*) a.nodes[1])).value.i;
    var newvar;
    newvar.name = "addition";
    newvar.value.i = num1 + num2;
    newvar.null_ = " ";
    return newvar;
  }
  else if(strcmp(a.name, "subnode") == 0) {
    long long num1 = interpret(*((node*) a.nodes[0])).value.i;
    long long num2 = interpret(*((node*) a.nodes[1])).value.i;
    var newvar;
    newvar.name = "subtraction";
    newvar.value.i = num1 - num2;
    newvar.null_ = " ";
    return newvar;
  }
  else if(strcmp(a.name, "mulnode") == 0) {
    long long num1 = interpret(*((node*) a.nodes[0])).value.i;
    long long num2 = interpret(*((node*) a.nodes[1])).value.i;
    var newvar;
    newvar.name = "multiplication";
    newvar.value.i = num1 * num2;
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
      newvar.null_ = " ";
      return newvar;
    }
    else {
      printf("%s:\n%s\n", "ZeroDivisionError", "Returning 0");
      var newvar;
      newvar.value.i = 0;
      return newvar;
    }
  }
  else {
    raise("NodeError", "Unexpected node", 0);
  }
}
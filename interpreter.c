#include "interpreter.h"
#include "parser.h"
#include "error.h"
#include <string.h>
#include <stdio.h>

long long interpret(node a) {
  if(strcmp(a.name, "num") == 0) {
    long long num = *((long long*) a.nodes[0]);
    return num;
  }
  else if(strcmp(a.name, "addnode") == 0) {
    long long num1 = interpret(*((node*) a.nodes[0]));
    long long num2 = interpret(*((node*) a.nodes[1]));
    return num1 + num2;
  }
  else if(strcmp(a.name, "subnode") == 0) {
    long long num1 = interpret(*((node*) a.nodes[0]));
    long long num2 = interpret(*((node*) a.nodes[1]));
    return num1 - num2;
  }
  else if(strcmp(a.name, "mulnode") == 0) {
    long long num1 = interpret(*((node*) a.nodes[0]));
    long long num2 = interpret(*((node*) a.nodes[1]));
    return num1 * num2;
  }
  else if(strcmp(a.name, "divnode") == 0) {
    long long num1 = interpret(*((node*) a.nodes[0]));
    long long num2 = interpret(*((node*) a.nodes[1]));
    if(num2 != 0) {
      return num1 / num2;
    }
    else {
      printf("%s:\n%s\n", "ZeroDivisionError", "Returning 0");
      return 0;
    }
  }
  else {
    raise("NodeError", "Unexpected node", 0);
  }
}
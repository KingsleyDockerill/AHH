#include "error.h"
#include <stdio.h>

char* raise(char* type, char* value, int ret) {
  if(ret) {
    return value;
  }
  else {
    printf("%s:\n%s\n", type, value);
    exit(1);
  }
}
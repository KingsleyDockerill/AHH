#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

char* raise(char* type, char* value, int ret) {
  if(ret) {
    return value;
  }
  else {
    printf("%s:\n%s\n", type, value);
    exit(1);
  }
}
#include "dict.h"

#ifndef dict__
  #define dict__
  typedef struct {
    void* keys;
    void* values;
  } dict;
#endif
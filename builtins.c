#include "builtins.h"
#include "error.h"
#include <stdio.h>

int is_try;

void trystatuschange(int try_) {
  is_try = try_;
}

char* read(char* path, char* mode) {
  FILE *fp;
  fp = fopen(path, mode);
  if(fp == NULL) {
    raise("FileExistsError", "Cannot find file", 0);
  }
  char* buff;
  fseek(fp, 0, SEEK_END); 
  int size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  char* fcontent = malloc(size);
  fread(fcontent, 1, size, fp);
  fclose(fp);
  buff = fcontent;
  return buff;
}
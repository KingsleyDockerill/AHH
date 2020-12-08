#include "builtins.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_try;

void trystatuschange(int try_) {
  is_try = try_;
}

void* print(char* toprint) {
  puts(toprint);
  // Don't forget to return NULL
  return NULL;
}

char* input(char* prompt) {
  char input[10000], c;
  for(int i = 0; (c = getchar()) != '\n'; i++) {
    if(i == 10000) {
      return raise("IOError", "Input cannot exede 9999 characters in length", is_try);
    }
    input[i] = c;
  }
  return input;
}

int execute(char* cmd) {
  return system(cmd);
}

char inchar() {
  return getchar();
}

char* read(char* path, char* mode) {
  FILE *fp;
  fp = fopen(path, mode);
  if(fp == NULL) {
    return raise("FileExistsError", "Cannot find file", is_try);
  }
  fseek(fp, 0, SEEK_END);
  int size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  char* fcontent = malloc(size);
  fread(fcontent, 1, size, fp);
  fclose(fp);
  return fcontent;
}

char* write(char* path, char* mode, char* towrite) {
  FILE *fp;
  fp = fopen(path, mode);
  if(fp == NULL) {
    return raise("FileExistsError", "Cannot find file", is_try);
  }
  fwrite(towrite, 1, strlen(towrite), fp);
  fclose(fp);
  return NULL;
}
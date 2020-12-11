#include "builtins.h"
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_try = 0;

void trystatuschange(int try_) {
  is_try = try_;
}

void* print(var toprint) {
  if(toprint.type == 'i') {
    printf("%lld", toprint.value.i);
  }
  else if(toprint.type == 's') {
    printf("%s", toprint.value.s);
  }
  else if(toprint.type == 'c') {
    putchar(toprint.value.c);
  }
  else {
    puts(raise("ArgumentError", "print got an unexpected argument type", is_try));
  }
  puts("");
  // Don't forget to return NULL
  return NULL;
}

char* input(char* prompt) {
  char input[10000], c;
  // Why do this instead of gets (which is equally bad)? Because if the input is too much, I can raise an error which is better than a segmentation fault
  for(int i = 0; (c = getchar()) != '\n'; i++) {
    if(i == 10000) {
      return raise("IOError", "Input cannot exceed 9999 characters in length", is_try);
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

int ascii(char char_) {
  return char_;
}

char chr(int int_) {
  return int_;
}

long long eval(char* a) {
  token* toks = generate(a);
  node parsed = parse(toks);
  return interpret(parsed).value.i;
}

long long chartoint(char a) {
  return a - '0';
}

char intochar(int a) {
  return a + '0';
}

char* inttostr(int number) {
  char* str;
  sprintf(str, "%d", number);
  return str;
}

int strtoint(char* str) {
  for(int i = 0; i < strlen(str); i++) {
    if(!isdigit(str[i])) {
      raise("CastError", "Cannot cast str that is not a number", is_try);
    }
  }
  return atoi(str);
}

// Functions not available
char* name() {
  #ifndef OS
    #ifdef _WIN32
      return "Windows";
    #elif _WIN64
      return "Windows"
    #elif __APPLE__ || __MACH__
      return "OSX";
    #elif __linux__
      return "Linux";
    #elif __FreeBSD__
      return "FreeBSD";
    #elif __unix || __unix__
      return "Unix";
    #else
      return "Other";
    #endif
  #endif
}
#include "interpreter.h"

void* print(var toprint);
char* input(char* prompt);
int execute(char* cmd);
char inchar();
char* read(char* path, char* mode);
char* write(char* path, char* mode, char* towrite);
int ascii(char char_);
char chr(int int_);
char* name();
long long eval(char* a);
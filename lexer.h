typedef struct {
    char* name;
    char type;
    union {
        int i;
        char c;
        char *s;
        float f;
        double d;
    } value;
} token;

token* generate(char* input) {
  token toks[10000];
  int pos = 0;
  for(int i = 0; input[i] != '\0'; i++) {
    token temp;
    switch(input[i]) {
      case '+' :
        printf("");
        token temp;
        temp.name = "add";
        temp.type = 's';
        temp.value.s = "+";
        toks[pos] = temp;
        ++pos;
        break;
      case '-' :
        printf("");
        temp.name = "sub";
        temp.type = 's';
        temp.value.s = "-";
        toks[pos] = temp;
        ++pos;
        break;
      case '*' :
        printf("");
        temp.name = "mul";
        temp.type = 's';
        temp.value.s = "*";
        toks[pos] = temp;
        ++pos;
        break;
      case '/' :
        printf("");
        temp.name = "div";
        temp.type = 's';
        temp.value.s = "/";
        toks[pos] = temp;
        ++pos;
        break;
      default :
        printf("\033[1;31;40mILLEGAL TOKEN: %s\033[1;31;40m", input[i]);
        exit(1);
        break;
    }
  }
  return toks;
}
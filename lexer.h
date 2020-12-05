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
  const static char* digits = "0123456789";
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
        break;
    }
  }
  return toks;
}
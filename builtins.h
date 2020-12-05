char* stolower(char* string) {
  char a[1000];
  for(int i; string[i] != '\0'; i++) {
    if((int)string[i] >= 65 && (int)string[i] <= 90 && string[i] != '\0') {
      i = (int) i;
      a[i] = (char) i + 32;
    }
    else {
      a[i] = string[i];
    }
  }
  return a;
}
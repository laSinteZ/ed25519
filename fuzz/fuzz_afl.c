#include <stdio.h>

extern int fuzz_sign_then_verify(const unsigned char *data, unsigned long long size);

int main() {
  const int MAXSIZE = 1 << 17;
  unsigned char input[MAXSIZE];
  unsigned long long size = scanf("%s", input);

  return fuzz_sign_then_verify(input, size);
}

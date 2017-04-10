#include <limits.h>
#include <stdio.h>

#define INT_BIT (sizeof(int) * CHAR_BIT)

int findsaw(int value);
char *toBin(int val);

int main() {
  printf("Serie 01 PSC 2016/17SV\n");
  int x = 0xEAEA476BL;
  printf("%d:\t%s\n", x, toBin(x));
  printf("%d\n", findsaw(x));
  return 0;
}

char *toBin(int val) {
  static char binary[39], output[39];  // with spaces
  for (int x = 0, msk = 1, spc = 1; x < sizeof(binary); msk <<= 1) {
    binary[x++] = (msk & val) == 0 ? '0' : '1';
    if (spc++ % 4 == 0) binary[x++] = ' ';
  }
  // reverse the array
  int index = 0, len = sizeof(binary);
  while (len > 0) {
    output[index++] = binary[--len];
  }
  return output;
}

int findsaw(int value) {
  int lookup[INT_BIT] = {0};
  int prv = (value >> 1) & 0b1, cur = 0, pos = 0, len = 0, max = 0;
  for (int x = 0; x < INT_BIT; x++) {
    cur = (value >> x) & 0b1;
    (prv != cur) ? (len++, pos = x) : (len = 0, pos++);
    prv = cur;
    printf("%d: %d[%d, %d]\n", x, cur, pos, len);
  }
  printf("\n");

  printf("%d - %d\n", pos, len);

  // printf("value: %d\n", value);

  return value;
}
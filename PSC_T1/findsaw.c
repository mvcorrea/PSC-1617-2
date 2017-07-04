#include <limits.h>
#include <stdio.h>
#define INT_BIT (sizeof(int) * CHAR_BIT)

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
  int prv = (value & 0b1); 
  //printf("x\tbit\tlen\tpos\tmaxlen\tmaxpos\n");
  int cur = 0, pos = 0, len = 0, maxpos = 0, maxlen = 0;
  for (int x = 0, flag = 0; x < INT_BIT; x++) { // cycle thru all bits
    cur = (value >> x) & 0b1;
    if(prv != cur){ // saw detected
      len++;
    } else {
      if (len > maxlen) maxlen = len, maxpos = pos;
      len = 1, pos = x, flag = 0;
    }
    prv = cur;
    //printf("%d\t%d\t%d\t%d\t%d\t%d\n", x, cur, len, pos, maxlen, maxpos);
  }
  return maxpos;
}

/*
int main() {
  printf("Serie 01 PSC 2016/17SV\n");
   int x = 0xEAEA476BL; // 23
   // int x = 0xAC54B56BL; // 6 
  
  printf("%d:\t%s\n", x, toBin(x));
  printf("\n%d\n", findsaw(x));
  return 0;
}
*/
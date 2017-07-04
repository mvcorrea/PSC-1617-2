#include <math.h>
#include <stdio.h>

// gcc -g -o float float.c -lm

// float representation..(32bits)
// S|EEEEEEEE|MMMMMMMMMMMMMMMMMMMMMMM
// 1|8|23
// MUST: http://www.h-schmidt.net/FloatConverter/IEEE754.html

#define SMSK 0x80000000
#define EMSK 0x7f800000
#define MMSK 0x7FFFFF

int floatSign(float val) {  // float signal
  unsigned *tmp = (unsigned *)&val;
  unsigned neg = (*tmp & SMSK);
  return neg ? -1 : 1;
}

// NOT USED
int floatExpt(float val) {  // float expoent
  unsigned *tmp = (unsigned *)&val;
  return pow(2, ((*tmp & EMSK) >> 23) - 127);
}

// NOT USED (using a float within)
// ASK !!! <----------------------------------------- (float as return value)
float floatMant(float val) {  // float mantissa
  unsigned *tmp = (unsigned *)&val;
  unsigned man = (*tmp & MMSK);
  float total = 1;
  int power = -1;
  for (int i = 22; i >= 0; i--) {
    unsigned bit = (man & (unsigned)(1 << i)) >> i;
    total += bit * pow(2, power--);
  }
  return total;
}

int getInt(float val) {
  unsigned *tmp = (unsigned *)&val;
  unsigned expBits = ((*tmp & EMSK) >> 23) - 127;
  unsigned manBits = (*tmp & MMSK) >> (23 - expBits);
  unsigned value = manBits + pow(2, expBits);
  return value;
}

int float_with_int_cmp(float fvalue, int ivalue) {
  int floatRep = floatSign(fvalue) * getInt(fvalue);
  printf("-> %d, %d\n", floatRep, ivalue);
  if (floatRep == ivalue) {
    return 0;
  } else {
    return floatRep > ivalue ? 1 : -1;
  }
}
/*
int main(int argc, char *argv[]) {
  // float tmp0 = -5.5; // 1|1000 0001|011 0000 0000 0000 0000 0000 (-1*2^2*1.375)
  // float tmp1 = 1.75;	// 0|1000 0000|110 0000 0000 0000 0000 0000 (1*2^1*1.75)
  // float see = floatSign(tmp0)*floatExpt(tmp0)*floatMant(tmp0);
  // printf("%f\n", see);

  printf("%d\n", float_with_int_cmp(3.75, -5));
  printf("%d\n", float_with_int_cmp(3.451, 3));
  printf("%d\n", float_with_int_cmp(-3.7, 2));
}
*/
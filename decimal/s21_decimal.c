
#include "s21_decimal.h"

#include <math.h>
#include <stdlib.h>

void s21_decimal_null(s21_decimal* count) {
  for (int i = 0; i < 4; ++i) {
    count->bits[i] = 0;
  }
}

int get_bit(s21_decimal dst, int n) {
  unsigned int i = 0;
  if (n > 95) {
    i = 3;
    n -= 96;
  } else if ((n < 96) && (n > 63)) {
    i = 2;
    n -= 64;
  } else if ((n < 64) && (n > 31)) {
    i = 1;
    n -= 32;
  }
  unsigned int mask = 1 << n;
  int result = mask & dst.bits[i];
  if (result) {
    result = 1;
  } else {
    result = 0;
  }
  return result;
}

void set_bit(s21_decimal* dst, int n, int bit) {
  unsigned int i = 0;
  if (n > 95) {
    i = 3;
    n -= 96;
  } else if ((n < 96) && (n > 63)) {
    i = 2;
    n -= 64;
  } else if ((n < 64) && (n > 31)) {
    i = 1;
    n -= 32;
  }
  unsigned int mask = 1 << n;
  if (bit) {
    dst->bits[i] |= mask;
  } else {
    mask = ~mask;
    dst->bits[i] &= mask;
  }
}

long long unsigned int convert_mantissa_to_int(s21_decimal dst) {
  long long unsigned int result = 0;
  for (int i = 95; i >= 0; --i) {
    result = result * 2 + get_bit(dst, i);
  }
  return result;
}

// void bits_state(int x) {
//   for (int i = 31; i >= 0; --i) {
//     printf("%d", get_bit(x, i));
//   }
//   // printf("\n");
// }

int s21_from_int_to_decimal(int src, s21_decimal* dst) {
  s21_decimal_null(dst);
  dst->bits[0] = abs(src);
  if (src < 0) {
    dst->bits[3] = MINUS;
  }
  return 0;
}

// int add(char src1, char src2, int result) {
//   result = src1 + src2;
//   // result += 2;
//   //  result &= 0b10000000;
//   //  result += 0b00000001;
//   bits_state(result);
//   return 0;
// }

int main() {
  // int b = 256;
  // bits_state(b);
  s21_decimal d = {0};
  // s21_from_int_to_decimal(0, &d);
  //  for (int j = 0; j < 128; ++j) {
  //    set_bit(&d, j, 1);
  //  }
  set_bit(&d, 63, 1);
  for (int i = 127; i >= 0; --i) {
    printf("%d", get_bit(d, i));
  }
  printf("\n");
  long long unsigned int m = convert_mantissa_to_int(d);
  printf("%llu\n", m);
  return 0;
}

// int main() {

//   int a = 6;
//   bits_state(a);
//   return 0;
// }
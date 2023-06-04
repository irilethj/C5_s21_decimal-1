#include <stdio.h>

#define BIT_1 0x80
#define BIT_2 0x40
#define BIT_3 0x20
#define BIT_4 0x10
#define BIT_5 0x08
#define BIT_6 0x04
#define BIT_7 0x02
#define BIT_8 0x01
#define MINUS 2147483648

void print_bits_state(unsigned char x) {
  printf("%d - ", x);
  printf("%d", (x & BIT_1) ? 1 : 0);
  printf("%d", (x & BIT_2) ? 1 : 0);
  printf("%d", (x & BIT_3) ? 1 : 0);
  printf("%d", (x & BIT_4) ? 1 : 0);
  printf("%d", (x & BIT_5) ? 1 : 0);
  printf("%d", (x & BIT_6) ? 1 : 0);
  printf("%d", (x & BIT_7) ? 1 : 0);
  printf("%d", (x & BIT_8) ? 1 : 0);
}
typedef struct {
  unsigned int bits[4];
} s21_decimal;

int main() {
  s21_decimal d = {0};
  d.bits[0] |= MINUS;
  printf("%d\n", d.bits[0]);
  // print_bits_state(a);
  return 0;
}
#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int status = OK;
  long long int bits = 0;
  if (s21_get_bit(&src, 31) && s21_get_bit(&src, 0) &&
      src.bits[0] == 2147483649 && src.bits[3] == 0) {
    src.bits[0] -= 2;
    s21_set_bit(&src, 127, 1);
  }
  for (int i = 95; i >= 0; i--)
    if (s21_get_bit(&src, i)) {
      bits = i;
      i = 0;
    }
  int power = s21_get_pow(src);
  for (int i = 0; i < power; i++) bits -= 4;

  if (bits > 32 || power > 28)
    status = CONVERTATION_ERROR;
  else {
    double number = 0;
    for (int i = 0; i <= (4 * power) + bits; i++)
      number += pow(2, i) * s21_get_bit(&src, i);
    number /= pow(10, power);
    if (s21_get_bit(&src, 127)) number *= -1;
    *dst = number;
  }

  return status;
}
#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int status = OK;
  long long int bits = 0;
  for (int i = 95; i >= 0; i--)
    if (s21_get_bit(&src, i)) {
      bits = i;
      i = 0;
    }
  int power = s21_get_pow(src);

  double number = 0;
  for (int i = 0; i <= bits; i++) number += pow(2, i) * s21_get_bit(&src, i);
  number = number / pow(10, power);
  if (s21_get_bit(&src, 127)) number *= -1;
  *dst = number;
  return status;
}
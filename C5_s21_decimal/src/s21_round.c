#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int power = s21_get_pow(value);
  int sign = s21_get_bit(&value, 127);
  float remain_fl = 0;
  s21_decimal one = {0};
  s21_from_int_to_decimal(1, &one);
  while (power > 1) {
    s21_division_by_10(&value);
    power--;
  }
  if (power != 0) {
    s21_decimal copy = value;
    s21_division_by_10(&value);
    s21_decimal remain = {0};
    s21_sub(copy, value, &remain);
    s21_from_decimal_to_float(remain, &remain_fl);
    if (fabs(remain_fl) > 0.5) {
      if (sign)
        s21_sub(value, one, &value);
      else
        s21_add(value, one, &value);
    } else if (fabsl(remain_fl) == 0.5) {
      if (s21_get_bit(&value, 0) == 1) {
        if (sign)
          s21_sub(value, one, &value);
        else
          s21_add(value, one, &value);
      }
    }
  }
  for (int i = 0; i < 4; i++) result->bits[i] = value.bits[i];
  return OK;
}
#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int err_num = OK;
  int sign = s21_check_sign(value);
  s21_decimal one = {0};
  s21_from_int_to_decimal(1, &one);
  s21_truncate(value, result);
  if (sign == 1 && !s21_is_equal(value, *result)) {
    s21_sub(*result, one, result);
  }
  s21_set_sign(result, sign);
  return err_num;
}
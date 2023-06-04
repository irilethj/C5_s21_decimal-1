#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int powFirst = 0;
  int powSecond = 0;
  powFirst = s21_get_pow(value_1);
  powSecond = s21_get_pow(value_2);
  s21_decimal_null(result);
  s21_decimal tmpRes;
  s21_decimal_null(&tmpRes);
  int status = 0;
  int shift = 0;
  for (int i = 95; i >= 0; i--) {
    s21_decimal tmpSecond;
    s21_decimal_null(&tmpSecond);
    tmpSecond = value_2;
    if (s21_get_bit(&value_1, 95 - i)) {
      int t = 95 - i;
      for (int j = 0; j < t; j++) {
        s21_shift_decimal_left(&tmpSecond);
      }
      status = s21_add(tmpSecond, tmpRes, &tmpRes);
    }
    shift++;
  }

  for (int i = 95; i >= 0; i--) {
    s21_set_bit(result, i, s21_get_bit(&tmpRes, i));
  }

  if (s21_check_sign(value_1) == 1 && s21_check_sign(value_2) == 1) {
    s21_set_sign(result, 0);
  } else if (s21_check_sign(value_1) == 0 && s21_check_sign(value_2) == 0) {
    s21_set_sign(result, 0);
  } else if ((s21_check_sign(value_1) == 0 && s21_check_sign(value_2) == 1) ||
             (s21_check_sign(value_1) == 1 && s21_check_sign(value_2) == 0)) {
    s21_set_sign(result, 1);
  }

  if ((powFirst + powSecond) > 28 && s21_check_sign(*result)) status = 2;
  if ((powFirst + powSecond) > 28 && !s21_check_sign(*result)) status = 1;

  s21_set_pow(result, powFirst + powSecond);

  return status;
}

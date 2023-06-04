#include "s21_decimal.h"

int s21_is_greater(s21_decimal value1, s21_decimal value2) {
  int res = 1;
  int sign1 = s21_check_sign(value1);
  int sign2 = s21_check_sign(value2);
  if ((sign1 == 1) && (sign2 == 0)) {
    res = 0;
  } else if ((sign1 == 0) && (sign2 == 1)) {
    if (s21_check_is_zero(value1) == 1 && s21_check_is_zero(value2) == 1) {
      res = 0;
    } else {
      res = 1;
    }
  } else {
    if (s21_is_less_or_equal(value1, value2) == 1) {
      res = 0;
    }
  }

  return res;
}
#include "s21_decimal.h"

int s21_is_equal(s21_decimal value1, s21_decimal value2) {
  int res = 1;
  int sign1 = s21_get_bit(&value1, 127);
  int sign2 = s21_get_bit(&value2, 127);

  if (sign1 == !sign2)
    res = (s21_check_is_zero(value1) && s21_check_is_zero(value2)) ? 1 : 0;
  else {
    s21_big_decimal bval1, bval2;
    s21_bdecimal_null(&bval1);
    s21_bdecimal_null(&bval2);
    s21_normalize(&value1, &value2);
    s21_transf_to_big(&bval1, value1);
    s21_transf_to_big(&bval2, value2);
    for (int t = 6; t >= 0 && res; t--) {
      if (bval1.bits[t] != bval2.bits[t]) {
        res = 0;
      }
    }
  }
  return res;
}
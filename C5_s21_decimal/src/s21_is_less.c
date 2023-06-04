#include "s21_decimal.h"

int s21_is_less(s21_decimal value1, s21_decimal value2) {
  int res = 1;
  int sign1 = s21_check_sign(value1);
  int sign2 = s21_check_sign(value2);
  if ((sign1 == 1) && (sign2 == 0)) {
    res = (s21_check_is_zero(value1) + s21_check_is_zero(value2) == 2) ? 0 : 1;
  } else if ((sign1 == 0) && (sign2 == 1)) {
    res = 0;
  } else {
    s21_big_decimal bigd1, bigd2;
    s21_bdecimal_null(&bigd1);
    s21_bdecimal_null(&bigd2);
    s21_normalize(&value1, &value2);
    s21_transf_to_big(&bigd1, value1);
    s21_transf_to_big(&bigd2, value2);
    if (s21_is_equal(value1, value2)) {
      res = 0;
    } else {
      for (int t = 6; t >= 0; t--) {
        if ((sign1 == 1 && bigd1.bits[t] < bigd2.bits[t]) ||
            (sign1 == 0 && bigd1.bits[t] > bigd2.bits[t])) {
          res = 0;
          break;
        } else if ((sign1 == 1 && bigd1.bits[t] > bigd2.bits[t]) ||
                   (sign1 == 0 && bigd1.bits[t] < bigd2.bits[t])) {
          res = 1;
          break;
        }
      }
    }
  }
  return res;
}
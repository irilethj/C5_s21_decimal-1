#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_decimal_null(result);
  int res = 0;
  int scale = s21_get_pow(value);
  int sign = s21_check_sign(value);
  *result = value;
  if (scale) {
    for (int t = scale; t > 0; t--) {
      s21_division_by_10(result);
    }
    float dec = 0.0;
    s21_from_decimal_to_float(*result, &dec);
    s21_set_pow(result, 0);
    s21_set_sign(result, sign);
  }
  return res;
}  // если все же будем работать с big_decimal, нужно написать отдельный
   // truncate под них
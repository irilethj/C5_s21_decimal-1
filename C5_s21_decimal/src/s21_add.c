#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = 0;
  s21_decimal_null(result);
  int error = s21_normalize(&value_1, &value_2);
  if (!error) {
    int pow_val = s21_get_pow(value_2);
    s21_set_pow(result, pow_val);
    if (s21_check_sign(value_1) && s21_check_sign(value_2)) {
      s21_set_sign(result, 1);
      status = s21_adding(value_1, value_2, result);
      if (status) status++;
    } else if (s21_check_sign(value_1) != s21_check_sign(value_2)) {
      if (s21_check_sign(value_1)) {
        s21_set_sign(&value_1, 0);
        s21_sub(value_2, value_1, result);
      } else {
        s21_set_sign(&value_2, 0);
        s21_sub(value_1, value_2, result);
      }
    } else
      status = s21_adding(value_1, value_2, result);
  } else
    status = error;
  return status;
}

int s21_adding(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int occupy = 0;
  for (int i = 0; i < 96; i++) {
    int bit1 = s21_get_bit(&value_1, i);
    int bit2 = s21_get_bit(&value_2, i);
    if (bit1 + bit2 + occupy == 1) {
      s21_set_bit(result, i, 1);
      occupy = 0;
    } else if (bit1 + bit2 + occupy == 2)
      occupy = 1;
    else if (bit1 + bit2 + occupy == 3) {
      s21_set_bit(result, i, 1);
      occupy = 1;
    } else
      occupy = 0;
  }
  return occupy;
}
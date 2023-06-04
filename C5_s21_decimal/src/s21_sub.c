#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = OK;
  s21_decimal_null(result);
  int error = s21_normalize(&value_1, &value_2);
  int sign1 = s21_get_bit(&value_1, 127);
  int sign2 = s21_get_bit(&value_2, 127);
  if (!error) {
    int pow_val = s21_get_pow(value_1);
    s21_set_pow(result, pow_val);
    if (sign1 && sign2) {
      if (s21_is_less(value_1, value_2)) {
        s21_substruction(value_1, value_2, result);
        s21_set_sign(result, 1);
      } else
        s21_substruction(value_2, value_1, result);
    } else if (sign1 && !sign2) {
      s21_set_sign(result, 1);
      s21_set_sign(&value_1, 0);
      status = s21_adding(value_1, value_2, result);
      if (status) status++;
    } else if (!sign1 && sign2) {
      s21_set_sign(&value_2, 0);
      status = s21_adding(value_1, value_2, result);
    } else {
      if (s21_is_less(value_1, value_2)) {
        s21_substruction(value_2, value_1, result);
        s21_set_sign(result, 1);
      } else
        s21_substruction(value_1, value_2, result);
    }
  } else
    status = error;

  return status;
}

int s21_substruction(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result) {
  int occupy = 0;
  for (int i = 0; i <= 96; i++) {
    int bit1 = s21_get_bit(&value_1, i);
    int bit2 = s21_get_bit(&value_2, i);
    if (bit1 - bit2 - occupy == 1) {
      s21_set_bit(result, i, 1);
      occupy = 0;
    } else if (bit1 - bit2 - occupy == 0)
      occupy = 0;
    else if (bit1 - bit2 - occupy == -1) {
      occupy = 1;
      s21_set_bit(result, i, 1);
    } else if (bit1 - bit2 - occupy == 3)
      occupy = 1;
  }
  return occupy;
}
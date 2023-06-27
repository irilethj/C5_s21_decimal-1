#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int return_code = 1;
  int x;
  x = s21_compare(value_1, value_2);
  if (x != -1) {
    return_code = 0;
  }
  return return_code;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int return_code = 1;
  int x;
  x = s21_compare(value_1, value_2);
  if (x != 1) {
    return_code = 0;
  }
  return return_code;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int return_code = 1;
  int x;
  x = s21_compare(value_1, value_2);
  if (x != 0) {
    return_code = 0;
  }
  return return_code;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int return_code = 0;
  int x;
  x = s21_compare(value_1, value_2);
  if (x == 0 || x == -1) {
    return_code = 1;
  }
  return return_code;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int return_code = 0;
  int x;
  x = s21_compare(value_1, value_2);
  if (x == 0 || x == 1) {
    return_code = 1;
  }
  return return_code;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  int return_code = 0;
  int x;
  x = s21_compare(value_1, value_2);
  if (x == 1 || x == -1) {
    return_code = 1;
  }
  return return_code;
}

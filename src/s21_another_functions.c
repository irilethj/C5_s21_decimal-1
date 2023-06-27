#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal* result) {
  *result = value;
  if (s21_get_bit(*result, 127)) {
    s21_set_bit(result, 127, 0);
  } else {
    s21_set_bit(result, 127, 1);
  }
  return 0;
}

int s21_truncate(s21_decimal value, s21_decimal* result) {
  int scale_value = s21_get_scale(value);
  if (!scale_value) {
    *result = value;
  } else {
    s21_big_decimal big_value;
    s21_big_decimal int_part;
    int sign_value = s21_get_bit(value, 127);
    s21_move_to_big(&big_value, value);
    while (scale_value) {
      s21_division_by_ten(big_value, &int_part);
      big_value = int_part;
      --scale_value;
    }
    s21_bset_bit(&big_value, 255, sign_value);
    s21_move_back(big_value, result);
  }
  return 0;
}

int s21_round(s21_decimal value, s21_decimal* result) {
  int scale_value = s21_get_scale(value);
  if (!scale_value) {
    *result = value;
  } else {
    s21_big_decimal big_value;
    s21_big_decimal int_part;
    int sign_value = s21_get_bit(value, 127);
    int remaind = 0;
    s21_move_to_big(&big_value, value);
    while (scale_value) {
      remaind = s21_division_by_ten(big_value, &int_part);
      big_value = int_part;
      --scale_value;
    }
    if (remaind > 4) {
      s21_big_decimal tmp;
      s21_big_decimal unit = {0};
      unit.bits[0] = 1;
      s21_add_for_division(big_value, unit, &tmp);
      big_value = tmp;
    }
    s21_bset_bit(&big_value, 255, sign_value);
    s21_move_back(big_value, result);
  }
  return 0;
}

int s21_floor(s21_decimal value, s21_decimal* result) {
  int scale_value = s21_get_scale(value);
  if (!scale_value) {
    *result = value;
  } else {
    s21_big_decimal big_value;
    s21_big_decimal int_part;
    s21_big_decimal tmp;
    s21_big_decimal unit = {0};
    unit.bits[0] = 1;
    int remaind = 0;
    int sign_value = s21_get_bit(value, 127);
    s21_move_to_big(&big_value, value);
    while (scale_value) {
      remaind += s21_division_by_ten(big_value, &int_part);
      big_value = int_part;
      --scale_value;
    }
    if (sign_value && remaind) {
      s21_add_for_division(big_value, unit, &tmp);
      big_value = tmp;
    }
    s21_bset_bit(&big_value, 255, sign_value);
    s21_move_back(big_value, result);
  }
  return 0;
}
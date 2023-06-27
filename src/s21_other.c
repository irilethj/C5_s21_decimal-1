#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal* result) {
  int result_flag = 0;
  s21_decimal_null(&*result);
  *result = value;
  result->bits[3] ^= MINUS;
  return result_flag;
}

int s21_truncate(s21_decimal value, s21_decimal* result) {
  int result_flag = 0;
  s21_decimal_null(result);
  if (!s21_get_scale(value)) {
    *result = value;
  } else {
    float float_value = 0.0;
    s21_from_decimal_to_float(value, &float_value);
    float_value = trunc(float_value);
    if (float_value < 0.0) {
      result->bits[3] |= MINUS;
      float_value *= -1;
    }
    for (int i = 0; float_value >= 1 && i < 96; i++) {
      float_value = floorl(float_value) / 2;
      if (float_value - floorl(float_value) > powl(10.0, -7)) {
        s21_set_bit(result, i, 1);
      }
    }
    result->bits[3] >>= 29;
    result->bits[3] <<= 29;
  }
  return result_flag;
}

int s21_floor(s21_decimal value, s21_decimal* result) {
  int return_val = 0;
  s21_decimal_null(result);
  if (!s21_get_scale(value)) {
    *result = value;
  } else {
    float float_value = 0.0;
    s21_from_decimal_to_float(value, &float_value);
    float_value = floorf(float_value);
    if (float_value < 0.0) {
      result->bits[3] |= MINUS;
      float_value *= -1;
    }
    for (int i = 0; float_value >= 1 && i < 96; i++) {
      float_value = floorl(float_value) / 2;
      if (float_value - floorl(float_value) > powl(10.0, -7)) {
        s21_set_bit(result, i, 1);
      }
    }
    result->bits[3] >>= 29;
    result->bits[3] <<= 29;
  }

  return return_val;
}

int s21_round(s21_decimal value, s21_decimal* result) {
  int return_val = 0;

  s21_decimal_null(result);
  float float_value = 0.0;
  s21_from_decimal_to_float(value, &float_value);
  float_value = roundf(float_value);
  if (float_value < 0.0) {
    result->bits[3] |= MINUS;
    float_value *= -1;
  }
  for (int i = 0; float_value >= 1 && i < 96; i++) {
    float_value = floorl(float_value) / 2;
    if (float_value - floorl(float_value) > powl(10.0, -7)) {
      s21_set_bit(result, i, 1);
    }
  }
  result->bits[3] >>= 29;
  result->bits[3] <<= 29;

  return return_val;
}
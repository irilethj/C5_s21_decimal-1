
#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal* dst) {
  s21_decimal_null(dst);
  dst->bits[0] = abs(src);
  if (src < 0) {
    dst->bits[3] = MINUS;
  }
  return 0;
}

int s21_from_decimal_to_int(s21_decimal src, int* dst) {
  int return_code = 0;
  double mantissa = s21_convert_mantissa_to_double(src);
  int scale = s21_get_scale(src);
  mantissa /= (pow(10, scale));
  if (scale > 28 || mantissa > 2147483647) {
    return_code = 1;
  } else {
    if (s21_get_bit(src, 127)) {
      mantissa *= -1;
    }
    *dst = mantissa;
  }

  return return_code;
}

int s21_from_float_to_decimal(float src, s21_decimal* dst) {
  int result_flag = 0;
  int scale = 0;
  int bit, int_length;
  float int_part, float_part;
  s21_decimal_null(&*dst);
  if (isinf(src) || src > 79228162514264337593543950335. || isnan(src) ||
      fabsf(src) < 1e-28) {
    s21_decimal_null(&*dst);
    result_flag = 1;
  } else if (src == 0.0f) {
    s21_decimal_null(&*dst);
  } else {
    float_part = modff(src, &int_part);
    int_length = s21_num_length(int_part);
    while (int_length < 7 && float_part != 0) {
      src = src * 10;
      scale++;
      float_part = modff(src, &int_part);
      int_length = s21_num_length(int_part);
    }
    src = roundf(src);
    if (src < 0) {
      dst->bits[3] |= MINUS;
      src = src * (-1);
    }
    dst->bits[3] >>= 16;
    dst->bits[3] |= scale;
    dst->bits[3] <<= 16;
    int i = 0;
    while (src >= 1) {
      src /= 2;
      bit = roundf(modff(src, &int_part));
      s21_set_bit(&*dst, i, bit);
      i++;
    }
  }
  return result_flag;
}

int s21_from_decimal_to_float(s21_decimal src, float* dst) {
  int result_flag = 0;
  int scale = s21_get_scale(src);
  *dst = 0.0;
  for (int i = 0; i < 96; i++) {
    if (s21_get_bit(src, i)) {
      *dst += pow(2, i);
    }
  }
  *dst = *dst / pow(10, scale);
  if (src.bits[3] >= 2147483648) {
    *dst = *dst * (-1);
  }
  if (isinf(*dst) || *dst > 79228162514264337593543950335. || isnan(*dst) ||
      fabsf(*dst) < 1e-28) {
    *dst = 0;
    result_flag = 1;
  }
  return result_flag;
}

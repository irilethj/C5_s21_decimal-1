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

void s21_dec_mult_ten(s21_decimal* value) {
  s21_decimal tmp = {0};
  s21_decimal copy_value = {0};
  s21_shift_decimal_left(value);
  copy_value = *value;
  s21_shift_decimal_left(value);
  s21_shift_decimal_left(value);
  s21_add_for_compare(*value, copy_value, &tmp);
  *value = tmp;
}

void s21_normalize(s21_decimal* value_1, s21_decimal* value_2) {
  int scale_value_1 = s21_get_scale(*value_1);
  int scale_value_2 = s21_get_scale(*value_2);
  int normalize_scale = 0;
  value_1->bits[3] = 0;
  value_2->bits[3] = 0;
  if (scale_value_1 > scale_value_2) {
    normalize_scale = scale_value_1 - scale_value_2;
    for (int i = 0; i < normalize_scale; ++i) {
      s21_dec_mult_ten(value_2);
    }
  } else if (scale_value_2 > scale_value_1) {
    normalize_scale = scale_value_2 - scale_value_1;
    for (int i = 0; i < normalize_scale; ++i) {
      s21_dec_mult_ten(value_1);
    }
  }
}

void s21_add_for_compare(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal* result) {
  int value_1_bit;
  int value_2_bit;
  int tmp = 0;
  for (int i = 0; i < 128; ++i) {
    value_1_bit = s21_get_bit(value_1, i);
    value_2_bit = s21_get_bit(value_2, i);
    if ((value_1_bit) && (value_2_bit) && (tmp)) {
      s21_set_bit(result, i, 1);
    }
    if (value_1_bit && value_2_bit) {
      tmp = 1;
    }
    if ((value_1_bit) && (!value_2_bit) && (!tmp)) {
      s21_set_bit(result, i, 1);
    }
    if ((!value_1_bit) && (value_2_bit) && (!tmp)) {
      s21_set_bit(result, i, 1);
    }
    if ((!value_1_bit) && (!value_2_bit) && (tmp)) {
      s21_set_bit(result, i, 1);
      tmp = 0;
    }
  }
}

int s21_shift_decimal_left(s21_decimal* count) {
  s21_decimal copy = {0};
  for (int i = 1; i < 128; i++)
    if (s21_get_bit(*count, i - 1)) {
      s21_set_bit(&copy, i, 1);
    }
  *count = copy;
  return copy.bits[3];
}

int s21_compare_mantissa(s21_decimal value_1, s21_decimal value_2,
                         int common_sign) {
  int return_code = -1;
  int equal = 0;
  s21_normalize(&value_1, &value_2);
  for (int i = 3; i >= 0; --i) {
    if (value_1.bits[i] == value_2.bits[i]) {
      ++equal;
    }
    if ((common_sign == 2) && (value_1.bits[i] != value_2.bits[i])) {
      if (value_1.bits[i] > value_2.bits[i]) {
        return_code = -1;
      } else {
        return_code = 1;
      }
      break;
    } else if (!common_sign && (value_1.bits[i] != value_2.bits[i])) {
      if (value_1.bits[i] < value_2.bits[i]) {
        return_code = -1;
      } else {
        return_code = 1;
      }
      break;
    }
  }
  if (equal == 4) {
    return_code = 0;
  }
  return return_code;
}

int s21_compare(s21_decimal value_1, s21_decimal value_2) {
  int return_code = -1, zero_decimal = 0;
  for (int i = 2; i >= 0; --i) {
    if (value_1.bits[i] || value_2.bits[i]) {
      zero_decimal = 1;
    }
  }
  if (!zero_decimal) {
    return_code = 0;
  } else if (s21_get_bit(value_1, 127) && (!s21_get_bit(value_2, 127))) {
    return_code = -1;
  } else if ((!s21_get_bit(value_1, 127)) && s21_get_bit(value_2, 127)) {
    return_code = 1;
  } else {
    int common_sign = s21_get_bit(value_1, 127) + s21_get_bit(value_2, 127);
    return_code = s21_compare_mantissa(value_1, value_2, common_sign);
  }
  return return_code;
}
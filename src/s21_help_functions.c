#include "s21_decimal.h"

void s21_decimal_null(s21_decimal* src) {
  for (int i = 0; i < 4; ++i) {
    src->bits[i] = 0;
  }
}
void s21_big_decimal_null(s21_big_decimal* src) {
  for (int i = 0; i < 8; ++i) {
    src->bits[i] = 0;
  }
}

int s21_get_bit(s21_decimal dst, int index) {
  unsigned int i = 0;
  if (index > 95) {
    i = 3;
    index -= 96;
  } else if ((index < 96) && (index > 63)) {
    i = 2;
    index -= 64;
  } else if ((index < 64) && (index > 31)) {
    i = 1;
    index -= 32;
  }
  unsigned int mask = 1 << index;
  int result = mask & dst.bits[i];
  if (result) {
    result = 1;
  } else {
    result = 0;
  }
  return result;
}

int s21_get_bit_int(int x, int index) {
  unsigned int mask = 1 << index;
  int result = mask & x;
  if (result) {
    result = 1;
  } else {
    result = 0;
  }
  return result;
}

void s21_set_bit(s21_decimal* dst, int index, int bit) {
  unsigned int i = 0;
  if (index > 95) {
    i = 3;
    index -= 96;
  } else if ((index < 96) && (index > 63)) {
    i = 2;
    index -= 64;
  } else if ((index < 64) && (index > 31)) {
    i = 1;
    index -= 32;
  }
  unsigned int mask = 1 << index;
  if (bit) {
    dst->bits[i] |= mask;
  } else {
    mask = ~mask;
    dst->bits[i] &= mask;
  }
}
void s21_set_scale(s21_big_decimal* dst, int scale) {
  for (int i = 0; i < 8; ++i) {
    s21_bset_bit(dst, i + 240, s21_get_bit_int(scale, i));
  }
}

int s21_get_scale(s21_decimal src) {
  int result = 0;
  int scale = 0;
  for (int i = 16; i <= 23; ++i) {
    result += pow(2, scale) * s21_get_bit(src, i + 96);
    ++scale;
  }
  return result;
}

int s21_bget_scale(s21_big_decimal src) {
  int result = 0;
  int scale = 0;
  for (int i = 240; i <= 247; ++i) {
    result += pow(2, scale) * s21_bget_bit(src, i);
    ++scale;
  }
  return result;
}

double s21_convert_mantissa_to_double(s21_decimal dst) {
  double result = 0;
  for (int i = 95; i >= 0; --i) {
    result = result * 2 + s21_get_bit(dst, i);
  }
  return result;
}

// void s21_print_decimal(s21_decimal src) {
//   printf("\n");
//   for (int i = 127; i >= 0; --i) {
//     printf("%d ", s21_get_bit(src, i));
//     if ((i == 96) || (i == 64) || (i == 32)) {
//       printf("\n");
//     }
//     if ((i == 120) || (i == 112)) {
//       printf(" ");
//     }
//   }
//   printf("\n\n");
// }

// void s21_print_dec_int(s21_decimal src) {
//   for (int i = 3; i >= 0; --i) {
//     printf("%u\n", src.bits[i]);
//   }
// }

void s21_shift_bdecimal_right(s21_big_decimal* count) {
  s21_big_decimal copy = {0};
  for (int i = 0; i < 224; i++)
    if (s21_bget_bit(*count, i + 1)) s21_bset_bit(&copy, i, 1);
  *count = copy;
}

void s21_subtraction(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal* result) {
  s21_big_decimal_null(result);
  s21_big_decimal additional_code_value_2 = {0};
  s21_big_decimal additional_code_result = {0};
  int compare = s21_compare_big_mantissa(value_1, value_2);
  s21_dopol_code(value_2, &additional_code_value_2);
  s21_add_for_division(value_1, additional_code_value_2, result);
  if (compare == -1) {
    s21_dopol_code(*result, &additional_code_result);
    for (int i = 6; i >= 0; --i) {
      result->bits[i] = additional_code_result.bits[i];
    }
  }
}

// void s21_print_int(int x) {
//   for (int i = 7; i >= 0; --i) {
//     printf("%d", s21_get_bit_int(x, i));
//   }
//   printf("\n");
// }

void s21_dopol_code(s21_big_decimal value, s21_big_decimal* result) {
  for (int i = 6; i >= 0; --i) {
    result->bits[i] = ~value.bits[i];
  }
  s21_big_decimal unit = {0};
  s21_big_decimal tmp = {0};
  unit.bits[0] = 1;
  s21_add_for_division(*result, unit, &tmp);
  *result = tmp;
}

int s21_compare_big_mantissa(s21_big_decimal value_1, s21_big_decimal value_2) {
  int return_code;
  int equal = 0;
  for (int i = 6; i >= 0; --i) {
    if (value_1.bits[i] == value_2.bits[i]) {
      ++equal;
    }
    if (value_1.bits[i] != value_2.bits[i]) {
      if (value_1.bits[i] < value_2.bits[i]) {
        return_code = -1;
      } else {
        return_code = 1;
      }
      break;
    }
  }
  if (equal == 7) {
    return_code = 0;
  }
  return return_code;
}

int s21_shift_big_decimal_left(s21_big_decimal* count) {
  s21_big_decimal copy = {0};
  for (int i = 1; i < 224; i++)
    if (s21_bget_bit(*count, i - 1)) {
      s21_bset_bit(&copy, i, 1);
    }
  *count = copy;
  return 0;
}

void s21_bset_bit(s21_big_decimal* dst, int index, int bit) {
  unsigned int i = index / 32;
  index %= 32;
  unsigned int mask = 1 << index;
  if (bit) {
    dst->bits[i] |= mask;
  } else {
    mask = ~mask;
    dst->bits[i] &= mask;
  }
}

int s21_dischage(s21_big_decimal* divide_by_10, s21_big_decimal* get) {
  s21_big_decimal_null(get);
  s21_big_decimal ten = {0};
  ten.bits[0] = 10;
  int less = 1;
  int dischage = 0;
  int division_is_possible = 0;
  int compare;
  while (less) {
    compare = s21_compare_big_mantissa(*divide_by_10, ten);
    if (!compare) {
      s21_bset_bit(get, 0, 1);
      less = 0;
      division_is_possible = 1;
    } else if (compare == -1) {
      less = 0;
    } else {
      s21_shift_big_decimal_left(&ten);
      ++dischage;
    }
  }
  if (dischage) {
    if (compare == -1) {
      s21_shift_bdecimal_right(&ten);
      s21_bset_bit(get, (dischage - 1), 1);
    } else if (!compare) {
      s21_big_decimal_null(get);
      s21_bset_bit(get, (dischage), 1);
    }
    *divide_by_10 = ten;
    division_is_possible = 1;
  }
  return division_is_possible;
}

int s21_division_by_ten(s21_big_decimal value, s21_big_decimal* int_part) {
  s21_big_decimal_null(int_part);
  s21_big_decimal copy_value = value;
  s21_big_decimal tmp = {0};
  s21_big_decimal get;
  int division_is_possible = s21_dischage(&copy_value, &get);
  while (division_is_possible) {
    s21_add_for_division(*int_part, get, &tmp);
    *int_part = tmp;
    s21_subtraction(value, copy_value, &tmp);
    value = tmp;
    copy_value = value;
    division_is_possible = s21_dischage(&copy_value, &get);
  }
  return value.bits[0];
}

// void s21_print_bdec_int(s21_big_decimal src) {
//   s21_big_decimal int_part;
//   s21_big_decimal zero = {0};
//   int remaind;
//   int arr[100] = {0};
//   remaind = s21_division_by_ten(src, &int_part);
//   int not_zero = s21_compare_big_mantissa(int_part, zero);
//   int count = 99;
//   while (not_zero == 1) {
//     arr[count] = remaind;
//     src = int_part;
//     remaind = s21_division_by_ten(src, &int_part);
//     not_zero = s21_compare_big_mantissa(int_part, zero);
//     --count;
//   }
//   arr[count] = src.bits[0];
//   printf(" # ");
//   for (int i = count, j = 1; i < 100; ++i, ++j) {
//     if (j == 3) {
//       printf(" ");
//       j = 0;
//     }
//     printf("%d", arr[i]);
//   }
//   printf(" #");
//   printf("\n");
// }

void s21_move_to_big(s21_big_decimal* big_value, s21_decimal value) {
  s21_big_decimal_null(big_value);
  for (int i = 2; i >= 0; --i) {
    big_value->bits[i] = value.bits[i];
  }
  big_value->bits[7] = value.bits[3];
}

// void s21_print_big_decimal(s21_big_decimal src) {
//   printf("\n");
//   for (int i = 255; i >= 0; --i) {
//     printf("%d ", s21_bget_bit(src, i));
//     if ((i == 224) || (i == 192) || (i == 160) || (i == 128)) {
//       printf("\n");
//     }
//     if ((i == 96) || (i == 64) || (i == 32)) {
//       printf("\n");
//     }
//     if ((i == 248) || (i == 240)) {
//       printf(" ");
//     }
//   }
//   printf("\n\n");
// }

int s21_bget_bit(s21_big_decimal dst, int index) {
  unsigned int i = index / 32;
  index %= 32;
  unsigned int mask = 1 << index;
  int result = mask & dst.bits[i];
  if (result) {
    result = 1;
  } else {
    result = 0;
  }
  return result;
}

void s21_add_for_division(s21_big_decimal value_1, s21_big_decimal value_2,
                          s21_big_decimal* result) {
  s21_big_decimal_null(result);
  int value_1_bit;
  int value_2_bit;
  int tmp = 0;
  for (int i = 0; i < 224; ++i) {
    value_1_bit = s21_bget_bit(value_1, i);
    value_2_bit = s21_bget_bit(value_2, i);
    if ((value_1_bit) && (value_2_bit) && (tmp)) {
      s21_bset_bit(result, i, 1);
    }
    if (value_1_bit && value_2_bit) {
      tmp = 1;
    }
    if ((value_1_bit) && (!value_2_bit) && (!tmp)) {
      s21_bset_bit(result, i, 1);
    }
    if ((!value_1_bit) && (value_2_bit) && (!tmp)) {
      s21_bset_bit(result, i, 1);
    }
    if ((!value_1_bit) && (!value_2_bit) && (tmp)) {
      s21_bset_bit(result, i, 1);
      tmp = 0;
    }
  }
}

void s21_bnormalize(s21_big_decimal* value_1, s21_big_decimal* value_2) {
  int scale_value_1 = s21_bget_scale(*value_1);
  int scale_value_2 = s21_bget_scale(*value_2);
  int normalize_scale = 0;
  if (scale_value_1 > scale_value_2) {
    normalize_scale = scale_value_1 - scale_value_2;
    for (int i = 0; i < normalize_scale; ++i) {
      s21_bdec_mult_ten(value_2);
    }
  } else if (scale_value_2 > scale_value_1) {
    normalize_scale = scale_value_2 - scale_value_1;
    for (int i = 0; i < normalize_scale; ++i) {
      s21_bdec_mult_ten(value_1);
    }
  }
}

void s21_bdec_mult_ten(s21_big_decimal* value) {
  s21_big_decimal tmp = {0};
  s21_big_decimal copy_value = {0};
  s21_shift_big_decimal_left(value);
  copy_value = *value;
  s21_shift_big_decimal_left(value);
  s21_shift_big_decimal_left(value);
  s21_add_for_division(*value, copy_value, &tmp);
  *value = tmp;
}

void s21_move_back(s21_big_decimal big_value, s21_decimal* value) {
  for (int i = 2; i >= 0; --i) {
    value->bits[i] = big_value.bits[i];
  }
  value->bits[3] = big_value.bits[7];
}

int s21_check_and_transfer(s21_big_decimal value, s21_decimal* result) {
  int check = 0;
  check = s21_check_overflow(value);
  if (check) { 
    int scale_value = s21_bget_scale(value);
    int sign_value = s21_bget_bit(value, 255);
    int remaind = 0;
    int prev_remaind = 0;
    if (scale_value) {
      s21_big_decimal int_part = {0};
      while (scale_value) {
        prev_remaind += remaind;
        remaind = s21_division_by_ten(value, &int_part);
        --scale_value;
        value = int_part;
        if (!s21_check_overflow(value)) {
          break;
        }
      }
    }
    check = s21_check_overflow(value);
    if (check) {
      if (sign_value) {
        check = 2;
      }
      s21_decimal_null(result);
    } else {
      s21_banking_rounding(&value, remaind, prev_remaind);
      s21_set_scale(&value, scale_value);
      s21_bset_bit(&value, 255, sign_value);
      s21_move_back(value, result);
    }
  } else {
    s21_move_back(value, result);
  }
  return check;
}


int s21_check_overflow(s21_big_decimal value) {
  int check = 0;
  for (int i = 96; i < 224; ++i) {
    if (s21_bget_bit(value, i)) {
      check = 1;
      break;
    }
  }
  return check;
}

int s21_dis(s21_big_decimal* dividend, s21_big_decimal divider,
            s21_big_decimal* get) {
  s21_big_decimal_null(get);
  int less = 1;
  int dischage = 0;
  int division_is_possible = 0;
  int compare;
  while (less) {
    compare = s21_compare_big_mantissa(*dividend, divider);
    if (!compare) {
      s21_bset_bit(get, 0, 1);
      less = 0;
      division_is_possible = 1;
    } else if (compare == -1) {
      less = 0;
    } else {
      s21_shift_big_decimal_left(&divider);
      ++dischage;
    }
  }
  if (dischage) {
    if (compare == -1) {
      s21_shift_bdecimal_right(&divider);
      s21_bset_bit(get, (dischage - 1), 1);
    } else if (!compare) {
      s21_big_decimal_null(get);
      s21_bset_bit(get, (dischage), 1);
    }
    *dividend = divider;
    division_is_possible = 1;
  }
  return division_is_possible;
}

void s21_division(s21_big_decimal value_1, s21_big_decimal value_2,
                  s21_big_decimal* int_part, s21_big_decimal* remaind) {
  s21_big_decimal_null(int_part);
  s21_big_decimal_null(remaind);
  s21_big_decimal dividend = value_1;
  s21_big_decimal tmp = {0};
  s21_big_decimal get;
  int division_is_possible = s21_dis(&dividend, value_2, &get);
  if (!division_is_possible) {
    *remaind = value_1;
  }
  while (division_is_possible) {
    s21_add_for_division(*int_part, get, &tmp);
    *int_part = tmp;
    s21_subtraction(value_1, dividend, remaind);
    value_1 = *remaind;
    dividend = value_1;
    division_is_possible = s21_dis(&dividend, value_2, &get);
  }
}

int s21_null_check(s21_decimal value) {
  int zero = 0;
  for (int i = 2; i >= 0; --i) {
    if (value.bits[i]) {
      ++zero;
    }
  }
  return zero;
}

int s21_bnull_check(s21_big_decimal value) {
  int zero = 0;
  for (int i = 6; i >= 0; --i) {
    if (value.bits[i]) {
      ++zero;
    }
  }
  return zero;
}

int s21_sign_result(s21_decimal value_1, s21_decimal value_2) {
  int sign = 1;
  if (s21_get_bit(value_1, 127) && s21_get_bit(value_2, 127)) {
    sign = 0;
  }
  if (!s21_get_bit(value_1, 127) && !s21_get_bit(value_2, 127)) {
    sign = 0;
  }
  return sign;
}
void s21_banking_rounding(s21_big_decimal* value, int remaind,
                          int prev_remaind) {
  int even = s21_bget_bit(*value, 0);
  int add_unit = 0;
  if (even && (remaind > 4)) {
    add_unit = 1;
  } else if (!even && (remaind == 5) && prev_remaind) {
    add_unit = 1;
  }
  if (add_unit) {
    s21_big_decimal tmp;
    s21_big_decimal unit = {0};
    unit.bits[0] = 1;
    s21_add_for_division(*value, unit, &tmp);
    *value = tmp;
  }
}

void s21_mult(s21_big_decimal value_1, s21_big_decimal value_2,
              s21_big_decimal* result) {
  s21_big_decimal copy_value_2 = value_2;
  s21_big_decimal tmp = {0};
  for (int i = 0; i < 96; ++i) {
    if (s21_bget_bit(value_1, i)) {
      for (int j = 0; j < i; ++j) {
        s21_shift_big_decimal_left(&copy_value_2);
      }
      s21_add_for_division(*result, copy_value_2, &tmp);
      *result = tmp;
      copy_value_2 = value_2;
    }
  }
}

int s21_num_length(long long int int_part) {
  int int_part_length = 0;
  while (int_part != 0) {
    int_part /= 10;
    int_part_length++;
  }
  return int_part_length;
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

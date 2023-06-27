
#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int return_code = 0;
  s21_decimal_null(result);
  s21_big_decimal copy_value_1, copy_value_2;
  s21_big_decimal copy_result = {0};
  s21_move_to_big(&copy_value_1, value_1);
  s21_move_to_big(&copy_value_2, value_2);
  int sign_value_1 = s21_bget_bit(copy_value_1, 255);
  int sign_value_2 = s21_bget_bit(copy_value_2, 255);
  int sign_result = sign_value_1;
  int scale_value_1 = s21_bget_scale(copy_value_1);
  int scale_value_2 = s21_bget_scale(copy_value_2);
  int scale_result = scale_value_1;
  int compare;
  if (scale_value_1 < scale_value_2) {
    scale_result = scale_value_2;
  }
  s21_bnormalize(&copy_value_1, &copy_value_2);
  compare = s21_compare_big_mantissa(copy_value_1, copy_value_2);
  if ((sign_value_1 != sign_value_2) && compare == 0) {
    ;
  } else {
    if ((sign_value_1 && sign_value_2) || (!sign_value_1 && !sign_value_2)) {
      s21_add_for_division(copy_value_1, copy_value_2, &copy_result);
    } else if (sign_value_1 != sign_value_2) {
      s21_subtraction(copy_value_1, copy_value_2, &copy_result);
    }
    s21_set_scale(&copy_result, scale_result);
    if (compare == -1) {
      sign_result = sign_value_2;
    }
    s21_bset_bit(&copy_result, 255, sign_result);
    return_code = s21_check_and_transfer(copy_result, result);
  }
  return return_code;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int return_code = 0;
  s21_decimal_null(result);
  s21_big_decimal copy_value_1, copy_value_2;
  s21_big_decimal copy_result = {0};
  s21_move_to_big(&copy_value_1, value_1);
  s21_move_to_big(&copy_value_2, value_2);
  int sign_value_1 = s21_bget_bit(copy_value_1, 255);
  int sign_value_2 = s21_bget_bit(copy_value_2, 255);
  int sign_result = sign_value_1;
  int scale_value_1 = s21_bget_scale(copy_value_1);
  int scale_value_2 = s21_bget_scale(copy_value_2);
  int scale_result = scale_value_1;
  int compare;
  if (scale_value_1 < scale_value_2) {
    scale_result = scale_value_2;
  }
  s21_bnormalize(&copy_value_1, &copy_value_2);
  compare = s21_compare_big_mantissa(copy_value_1, copy_value_2);
  if ((sign_value_1 == sign_value_2) && (compare == 0)) {
    ;
  } else {
    if (sign_value_1 != sign_value_2) {
      s21_add_for_division(copy_value_1, copy_value_2, &copy_result);
    } else if (sign_value_1 == sign_value_2) {
      s21_subtraction(copy_value_1, copy_value_2, &copy_result);
      if (((compare == -1) && (!sign_value_1)) ||
          ((compare == 1) && (sign_value_1))) {
        sign_result = 1;
      }
    }
    s21_set_scale(&copy_result, scale_result);
    s21_bset_bit(&copy_result, 255, sign_result);
    return_code = s21_check_and_transfer(copy_result, result);
  }
  return return_code;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int return_code = 0;
  s21_decimal_null(result);
  if (!s21_null_check(value_2)) {
    return_code = 3;
  } else if (!s21_null_check(value_1)) {
    ;
  } else {
    s21_big_decimal copy_value_1, copy_value_2, int_part, remaind;
    s21_big_decimal copy_result = {0};
    s21_move_to_big(&copy_value_1, value_1);
    s21_move_to_big(&copy_value_2, value_2);
    int sign_result = s21_sign_result(value_1, value_2);
    int scale_result = 0;
    s21_bnormalize(&copy_value_1, &copy_value_2);
    s21_division(copy_value_1, copy_value_2, &int_part, &remaind);
    copy_result = int_part;
    s21_set_scale(&copy_result, scale_result);
    if (s21_bnull_check(remaind)) {
      copy_value_1 = remaind;
      int scale_remaind = scale_result;
      while (s21_bnull_check(remaind) && (scale_remaind < 29)) {
        s21_bdec_mult_ten(&copy_value_1);
        ++scale_remaind;
        s21_division(copy_value_1, copy_value_2, &int_part, &remaind);
      }
      s21_set_scale(&int_part, scale_remaind);
      s21_bnormalize(&copy_result, &int_part);
      s21_big_decimal tmp;
      s21_add_for_division(copy_result, int_part, &tmp);
      copy_result = tmp;
      s21_set_scale(&copy_result, scale_remaind);
    }
    s21_bset_bit(&copy_result, 255, sign_result);
    return_code = s21_check_and_transfer(copy_result, result);
  }
  return return_code;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int return_code = 0;
  s21_decimal_null(result);
  if (!s21_null_check(value_2) || !s21_null_check(value_1)) {
    ;
  } else {
    s21_big_decimal copy_value_1, copy_value_2;
    s21_big_decimal copy_result = {0};
    s21_move_to_big(&copy_value_1, value_1);
    s21_move_to_big(&copy_value_2, value_2);
    int sign_result = s21_sign_result(value_1, value_2);
    int scale_result;
    scale_result = s21_bget_scale(copy_value_1) + s21_bget_scale(copy_value_2);
    s21_mult(copy_value_1, copy_value_2, &copy_result);
    s21_set_scale(&copy_result, scale_result);
    s21_bset_bit(&copy_result, 255, sign_result);
    return_code = s21_check_and_transfer(copy_result, result);
  }
  return return_code;
}

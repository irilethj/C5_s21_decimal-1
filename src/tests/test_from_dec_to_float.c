#include "s21_test.h"

START_TEST(test_from_dec_to_float_1) {
  s21_decimal decimal;
  s21_decimal_null(&decimal);
  float f_value = 0.0000000001, res = 0;
  s21_from_float_to_decimal(f_value, &decimal);
  s21_from_decimal_to_float(decimal, &res);
  ck_assert_float_eq_tol(f_value, res, 10);
}
END_TEST

START_TEST(test_from_dec_to_float_2) {
  s21_decimal decimal;
  s21_decimal_null(&decimal);
  float f_value = -3.0, res = 0;
  s21_from_float_to_decimal(f_value, &decimal);
  s21_from_decimal_to_float(decimal, &res);
  ck_assert_float_eq(f_value, res);
}
END_TEST

START_TEST(test_from_dec_to_float_3) {
  s21_decimal decimal;
  s21_decimal_null(&decimal);
  float f_value = 0, res = 0;
  s21_from_float_to_decimal(f_value, &decimal);
  s21_from_decimal_to_float(decimal, &res);
  ck_assert_float_eq(f_value, res);
}
END_TEST

START_TEST(test_from_dec_to_float_4) {
  s21_decimal decimal;
  s21_decimal_null(&decimal);
  float f_value = 7.9e28, res = 0;
  s21_from_float_to_decimal(f_value, &decimal);
  s21_from_decimal_to_float(decimal, &res);
  ck_assert_float_eq(f_value, res);
}
END_TEST

Suite *test_from_dec_to_float(void) {
  Suite *s = suite_create("\033[42m-=test_from_dec_to_float=-\033[0m");
  TCase *tc = tcase_create("add_tc");

  tcase_add_test(tc, test_from_dec_to_float_1);
  tcase_add_test(tc, test_from_dec_to_float_2);
  tcase_add_test(tc, test_from_dec_to_float_3);
  tcase_add_test(tc, test_from_dec_to_float_4);

  suite_add_tcase(s, tc);
  return s;
}
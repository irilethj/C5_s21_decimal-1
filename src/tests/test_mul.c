#include "s21_test.h"

START_TEST(test_mul_1) {
  s21_decimal decimal_1;
  s21_decimal decimal_2;
  s21_decimal result;
  s21_decimal_null(&decimal_1);
  s21_decimal_null(&decimal_2);
  decimal_1.bits[0] = 1256;
  decimal_2.bits[0] = 1000;

  s21_decimal true_result;
  s21_decimal_null(&true_result);
  true_result.bits[0] = 1256000;

  int status = s21_mul(decimal_1, decimal_2, &result);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(result, true_result));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_mul_2) {
  s21_decimal decimal_1;
  s21_decimal decimal_2;
  s21_decimal result;
  s21_decimal_null(&decimal_1);
  s21_decimal_null(&decimal_2);

  decimal_1.bits[0] = 125236476;
  decimal_1.bits[3] = 393216;

  decimal_2.bits[0] = 364287140;
  decimal_2.bits[3] = MINUS + 196608;

  s21_decimal true_result;
  s21_decimal_null(&true_result);
  true_result.bits[0] = 1694409072;
  true_result.bits[1] = 10622208;
  true_result.bits[3] = 589824 + MINUS;

  int status = s21_mul(decimal_1, decimal_2, &result);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(result, true_result));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_mul_3) {
  s21_decimal decimal_1;
  s21_decimal decimal_2;
  s21_decimal result;
  s21_decimal_null(&decimal_1);
  s21_decimal_null(&decimal_2);

  decimal_1.bits[2] = 4294967295;

  decimal_2.bits[0] = 2;

  int status = s21_mul(decimal_1, decimal_2, &result);
  int true_status = 1;

  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_mul_4) {
  s21_decimal decimal_1;
  s21_decimal decimal_2;
  s21_decimal result;
  s21_decimal_null(&decimal_1);
  s21_decimal_null(&decimal_2);

  decimal_1.bits[0] = 4294967295;
  decimal_1.bits[1] = 4294967295;
  decimal_1.bits[2] = 2147483647;

  decimal_2.bits[0] = 2;

  s21_decimal true_result;
  s21_decimal_null(&true_result);
  true_result.bits[0] = 4294967294;
  true_result.bits[1] = 4294967295;
  true_result.bits[2] = 4294967295;

  int status = s21_mul(decimal_1, decimal_2, &result);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(result, true_result));
  ck_assert_int_eq(status, true_status);
}
END_TEST

Suite *test_mul(void) {
  Suite *s = suite_create("\033[41m-=test_mul=-\033[0m");
  TCase *tc = tcase_create("sub_tc");

  tcase_add_test(tc, test_mul_1);
  tcase_add_test(tc, test_mul_2);
  tcase_add_test(tc, test_mul_3);
  tcase_add_test(tc, test_mul_4);

  suite_add_tcase(s, tc);
  return s;
}
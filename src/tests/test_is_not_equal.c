#include "s21_test.h"

START_TEST(test_is_not_equal_1) {
  s21_decimal decimal_1;
  s21_decimal_null(&decimal_1);
  decimal_1.bits[0] = 178532910;
  decimal_1.bits[1] = 4081246736;
  decimal_1.bits[2] = 2119837296;
  decimal_1.bits[3] = 1769472;

  s21_decimal decimal_2;
  s21_decimal_null(&decimal_2);

  decimal_2.bits[0] = 178539999;
  decimal_2.bits[1] = 4081246736;
  decimal_2.bits[2] = 2119837296;
  decimal_2.bits[3] = 1769472;

  int status = s21_is_not_equal(decimal_1, decimal_2);
  int true_status = 1;

  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_is_not_equal_2) {
  s21_decimal decimal_1;
  s21_decimal_null(&decimal_1);
  decimal_1.bits[0] = 178532910;
  decimal_1.bits[1] = 4081246736;
  decimal_1.bits[2] = 2119837296;
  decimal_1.bits[3] = 1769472;

  s21_decimal decimal_2;
  s21_decimal_null(&decimal_2);

  decimal_2.bits[0] = 178532910;
  decimal_2.bits[1] = 4081246736;
  decimal_2.bits[2] = 2119837296;
  decimal_2.bits[3] = 1769472;

  int status = s21_is_not_equal(decimal_1, decimal_2);
  int true_status = 0;

  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_is_not_equal_3) {
  s21_decimal decimal_1;
  s21_decimal_null(&decimal_1);
  decimal_1.bits[0] = 178532910;
  decimal_1.bits[1] = 4081246736;
  decimal_1.bits[2] = 2119837999;
  decimal_1.bits[3] = 1769472;

  s21_decimal decimal_2;
  s21_decimal_null(&decimal_2);

  decimal_2.bits[0] = 178532910;
  decimal_2.bits[1] = 4081246736;
  decimal_2.bits[2] = 2119837296;
  decimal_2.bits[3] = 1769472;

  int status = s21_is_not_equal(decimal_1, decimal_2);
  int true_status = 1;

  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_is_not_equal_4) {
  s21_decimal decimal_1;
  s21_decimal_null(&decimal_1);
  decimal_1.bits[0] = 178532910;
  decimal_1.bits[1] = 4081246736;
  decimal_1.bits[2] = 2119837296;
  decimal_1.bits[3] = 2149253120;

  s21_decimal decimal_2;
  s21_decimal_null(&decimal_2);

  decimal_2.bits[0] = 178539999;
  decimal_2.bits[1] = 4081246736;
  decimal_2.bits[2] = 2119837296;
  decimal_2.bits[3] = 2149253120;

  int status = s21_is_not_equal(decimal_1, decimal_2);
  int true_status = 1;

  ck_assert_int_eq(status, true_status);
}
END_TEST

Suite *test_is_not_equal(void) {
  Suite *s = suite_create("\033[45m-=test_is_not_equal=-\033[0m");
  TCase *tc = tcase_create("add_tc");

  tcase_add_test(tc, test_is_not_equal_1);
  tcase_add_test(tc, test_is_not_equal_2);
  tcase_add_test(tc, test_is_not_equal_3);
  tcase_add_test(tc, test_is_not_equal_4);

  suite_add_tcase(s, tc);
  return s;
}
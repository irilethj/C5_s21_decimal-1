#include "s21_test.h"

START_TEST(test_truncate_1) {
  s21_decimal decimal;
  s21_decimal_null(&decimal);
  decimal.bits[0] = 178532910;
  decimal.bits[1] = 4081246736;
  decimal.bits[2] = 2119837296;
  decimal.bits[3] = 2149253120;
  s21_decimal ans;
  s21_decimal_null(&ans);
  s21_decimal true_ans;
  s21_decimal_null(&true_ans);
  true_ans.bits[0] = 39;
  true_ans.bits[3] = 2147483648;

  int status = s21_truncate(decimal, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_truncate_2) {
  s21_decimal decimal;
  s21_decimal_null(&decimal);
  decimal.bits[0] = 613478421;
  decimal.bits[3] = 196608;
  s21_decimal ans;
  s21_decimal_null(&ans);

  s21_decimal true_ans;
  s21_decimal_null(&true_ans);
  true_ans.bits[0] = 613478;

  int status = s21_truncate(decimal, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_truncate_3) {
  s21_decimal decimal;
  s21_decimal_null(&decimal);
  decimal.bits[0] = 0;
  decimal.bits[1] = 0;
  decimal.bits[2] = 0;
  decimal.bits[3] = 196608;

  s21_decimal ans;
  s21_decimal_null(&ans);

  s21_decimal true_ans;
  s21_decimal_null(&true_ans);
  true_ans.bits[0] = 0;

  int status = s21_truncate(decimal, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

Suite *test_truncate(void) {
  Suite *s = suite_create("\033[43m-=test_truncate=-\033[0m");
  TCase *tc = tcase_create("add_tc");

  tcase_add_test(tc, test_truncate_1);
  tcase_add_test(tc, test_truncate_2);
  tcase_add_test(tc, test_truncate_3);

  suite_add_tcase(s, tc);
  return s;
}
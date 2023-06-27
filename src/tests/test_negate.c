#include "s21_test.h"

START_TEST(test_negate_1) {
  s21_decimal dec;
  s21_decimal ans;
  s21_decimal_null(&dec);
  dec.bits[0] = 2814903;
  dec.bits[3] = 65536 + 2147483648;

  s21_decimal true_ans;
  s21_decimal_null(&true_ans);
  true_ans.bits[0] = 2814903;
  true_ans.bits[3] = 65536;

  int status = s21_negate(dec, &ans);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_negate_2) {
  s21_decimal dec;
  s21_decimal ans;
  s21_decimal_null(&dec);
  dec.bits[0] = 2814903;
  dec.bits[1] = 2384901;
  dec.bits[2] = 27498;
  dec.bits[3] = 0;

  s21_decimal true_ans;
  s21_decimal_null(&true_ans);
  true_ans.bits[0] = 2814903;
  true_ans.bits[1] = 2384901;
  true_ans.bits[2] = 27498;
  true_ans.bits[3] = 2147483648;

  int status = s21_negate(dec, &ans);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

Suite *test_negate(void) {
  Suite *s = suite_create("\033[43m-=test_negate=-\033[0m");
  TCase *tc = tcase_create("add_tc");

  tcase_add_test(tc, test_negate_1);
  tcase_add_test(tc, test_negate_2);

  suite_add_tcase(s, tc);
  return s;
}
#include "s21_test.h"

START_TEST(test_round_1) {
  s21_decimal dec;
  s21_decimal_null(&dec);
  dec.bits[0] = 178532910;
  dec.bits[1] = 4081246736;
  dec.bits[2] = 2119837296;
  dec.bits[3] = 2149253120;

  s21_decimal ans;
  s21_decimal_null(&ans);

  s21_decimal true_ans;
  s21_decimal_null(&true_ans);
  true_ans.bits[0] = 39;
  true_ans.bits[3] = 2147483648;

  int status = s21_round(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_round_2) {
  s21_decimal dec;
  s21_decimal_null(&dec);
  dec.bits[0] = 598769227;
  dec.bits[1] = 2903911868;
  dec.bits[2] = 4948073;
  dec.bits[3] = 1703936;

  s21_decimal ans;
  s21_decimal_null(&ans);

  s21_decimal true_ans;
  s21_decimal_null(&true_ans);
  true_ans.bits[0] = 1;
  int status = s21_round(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_round_3) {
  s21_decimal dec;
  s21_decimal_null(&dec);
  dec.bits[0] = 598769227;
  dec.bits[1] = 2903911868;
  dec.bits[2] = 4948073;
  dec.bits[3] = 1703936 + 2147483648;

  s21_decimal ans;
  s21_decimal_null(&ans);

  s21_decimal true_ans;
  s21_decimal_null(&true_ans);
  true_ans.bits[0] = 1;
  true_ans.bits[3] = 2147483648;
  int status = s21_round(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_round_4) {
  s21_decimal dec;
  s21_decimal_null(&dec);
  dec.bits[0] = 915492088;
  dec.bits[1] = 614240;
  dec.bits[3] = 655360 + 2147483648;

  s21_decimal ans;
  s21_decimal_null(&ans);

  s21_decimal true_ans;
  s21_decimal_null(&true_ans);
  true_ans.bits[0] = 263814;
  true_ans.bits[3] = 2147483648;
  int status = s21_round(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_round_5) {
  s21_decimal dec;
  s21_decimal_null(&dec);
  dec.bits[0] = 784662527;
  dec.bits[1] = 11641532;
  dec.bits[3] = 1114112;

  s21_decimal ans;
  s21_decimal_null(&ans);

  s21_decimal true_ans;
  s21_decimal_null(&true_ans);
  true_ans.bits[0] = 1;
  int status = s21_round(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

Suite *test_round(void) {
  Suite *s = suite_create("\033[43m-=test_round=-\033[0m");
  TCase *tc = tcase_create("add_tc");

  tcase_add_test(tc, test_round_1);
  tcase_add_test(tc, test_round_2);
  tcase_add_test(tc, test_round_3);
  tcase_add_test(tc, test_round_4);
  tcase_add_test(tc, test_round_5);
  suite_add_tcase(s, tc);
  return s;
}
#include "s21_test.h"

START_TEST(test_div_1) {
  s21_decimal decimal_1;
  s21_decimal decimal_2;
  s21_decimal result;
  s21_decimal_null(&decimal_1);
  s21_decimal_null(&decimal_2);
  decimal_1.bits[0] = 65536;
  decimal_2.bits[0] = 2;
  s21_decimal true_result;
  s21_decimal_null(&true_result);
  true_result.bits[0] = 32768;
  int status = s21_div(decimal_1, decimal_2, &result);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(result, true_result));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_div_2) {
  s21_decimal decimal_1;
  s21_decimal decimal_2;
  s21_decimal result;
  s21_decimal_null(&decimal_1);
  s21_decimal_null(&decimal_2);
  decimal_1.bits[0] = 9;
  decimal_1.bits[3] = 65536;
  decimal_2.bits[0] = 6;
  decimal_2.bits[3] = 65536;
  s21_decimal true_result;
  s21_decimal_null(&true_result);
  true_result.bits[0] = 15;
  true_result.bits[3] = 65536;
  int status = s21_div(decimal_1, decimal_2, &result);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(result, true_result));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_div_3) {
  s21_decimal decimal_1;
  s21_decimal decimal_2;
  s21_decimal result;
  s21_decimal_null(&decimal_1);
  s21_decimal_null(&decimal_2);
  decimal_1.bits[0] = 14;
  decimal_1.bits[3] = 65536;
  decimal_2.bits[0] = 9;
  decimal_2.bits[3] = 65536;

  s21_decimal true_result;
  s21_decimal_null(&true_result);
  true_result.bits[0] = 3280877796;
  true_result.bits[1] = 1621842184;
  true_result.bits[2] = 843268356;
  true_result.bits[3] = 1835008;
  int status = s21_div(decimal_1, decimal_2, &result);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(result, true_result));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_div_4) {
  s21_decimal decimal_1;
  s21_decimal decimal_2;
  s21_decimal result;
  s21_decimal_null(&decimal_1);
  s21_decimal_null(&decimal_2);
  decimal_1.bits[0] = 14;
  decimal_1.bits[3] = 65536;
  decimal_2.bits[0] = 9;
  decimal_2.bits[3] = 65536 + MINUS;

  s21_decimal true_result;
  s21_decimal_null(&true_result);
  true_result.bits[0] = 3280877796;
  true_result.bits[1] = 1621842184;
  true_result.bits[2] = 843268356;
  true_result.bits[3] = 1835008 + MINUS;
  int status = s21_div(decimal_1, decimal_2, &result);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(result, true_result));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_div_5) {
  s21_decimal decimal_1;
  s21_decimal decimal_2;
  s21_decimal result;
  s21_decimal_null(&decimal_1);
  s21_decimal_null(&decimal_2);
  decimal_1.bits[0] = 2814903;
  decimal_1.bits[3] = 65536;
  decimal_2.bits[0] = 0;
  decimal_2.bits[3] = 65536 + MINUS;
  int status = s21_div(decimal_1, decimal_2, &result);
  int true_status = 3;
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_div_6) {
  s21_decimal decimal_1;
  s21_decimal decimal_2;
  s21_decimal result;
  s21_decimal_null(&decimal_1);
  s21_decimal_null(&decimal_2);
  decimal_1.bits[0] = 0;
  decimal_1.bits[3] = 65536;
  decimal_2.bits[0] = 4578783;
  s21_decimal true_result;
  s21_decimal_null(&true_result);
  true_result.bits[0] = 0;
  true_result.bits[1] = 0;
  true_result.bits[2] = 0;
  true_result.bits[3] = 0;
  int status = s21_div(decimal_1, decimal_2, &result);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(result, true_result));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_div_7) {
  s21_decimal decimal_1;
  s21_decimal decimal_2;
  s21_decimal result;
  s21_decimal_null(&decimal_1);
  s21_decimal_null(&decimal_2);
  decimal_1.bits[0] = 4294967294;
  decimal_1.bits[1] = 4294967295;
  decimal_1.bits[2] = 4294967295;
  decimal_2.bits[0] = 1;
  decimal_2.bits[3] = 1179648;

  int status = s21_div(decimal_1, decimal_2, &result);
  int true_status = 1;
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_div_8) {
  s21_decimal decimal_1;
  s21_decimal decimal_2;
  s21_decimal result;
  s21_decimal_null(&decimal_1);
  s21_decimal_null(&decimal_2);
  decimal_2.bits[0] = 4294967294;
  decimal_2.bits[1] = 4294967295;
  decimal_2.bits[2] = 4294967295;
  decimal_1.bits[0] = 1;
  decimal_1.bits[3] = 1179648;

  int status = s21_div(decimal_1, decimal_2, &result);
  int true_status = 0;
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_div_9) {
  s21_decimal decimal_1;
  s21_decimal decimal_2;
  s21_decimal result;
  s21_decimal_null(&decimal_1);
  s21_decimal_null(&decimal_2);
  decimal_1.bits[0] = 4294967295;
  decimal_1.bits[1] = 4294967295;
  decimal_1.bits[2] = 4294967295;
  decimal_1.bits[3] = 1179648;
  decimal_2.bits[0] = 1;
  decimal_2.bits[3] = 1179648;

  int status = s21_div(decimal_1, decimal_2, &result);
  s21_decimal true_result;
  s21_decimal_null(&true_result);
  true_result.bits[0] = 4294967295;
  true_result.bits[1] = 4294967295;
  true_result.bits[2] = 4294967295;
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(result, true_result));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_div_10) {
  s21_decimal decimal_1;
  s21_decimal decimal_2;
  s21_decimal result;
  s21_decimal_null(&decimal_1);
  s21_decimal_null(&decimal_2);
  decimal_1.bits[0] = 4294967295;
  decimal_1.bits[1] = 4294967295;
  decimal_1.bits[2] = 4294967295;
  decimal_2.bits[0] = 4294967295;
  decimal_2.bits[1] = 4294967295;
  decimal_2.bits[2] = 4294967295;

  int status = s21_div(decimal_1, decimal_2, &result);
  s21_decimal true_result;
  s21_decimal_null(&true_result);
  true_result.bits[0] = 1;
  true_result.bits[1] = 0;
  true_result.bits[2] = 0;
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(result, true_result));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_div_11) {
  s21_decimal decimal_1;
  s21_decimal decimal_2;
  s21_decimal result;
  s21_decimal_null(&decimal_1);
  s21_decimal_null(&decimal_2);
  s21_decimal_null(&result);

  decimal_1.bits[0] = 1996679748;
  decimal_1.bits[1] = 4232406046;
  decimal_1.bits[2] = 151016884;
  decimal_1.bits[3] = 2148335616;

  decimal_2.bits[0] = 2671657829;
  decimal_2.bits[1] = 165868194;
  decimal_2.bits[2] = 0;
  decimal_2.bits[3] = 327680;

  s21_decimal true_result;
  s21_decimal_null(&true_result);
  true_result.bits[0] = 178532910;
  true_result.bits[1] = 4081246736;
  true_result.bits[2] = 2119837296;
  true_result.bits[3] = 2149253120;

  int status = s21_div(decimal_1, decimal_2, &result);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(result, true_result));
  ck_assert_int_eq(status, true_status);
}

START_TEST(test_div_12) {
  s21_decimal decimal_1;
  s21_decimal decimal_2;
  s21_decimal result;
  s21_decimal_null(&decimal_1);
  s21_decimal_null(&decimal_2);
  s21_decimal_null(&result);

  decimal_1.bits[0] = 1188260494;
  decimal_1.bits[1] = 2547073670;
  decimal_1.bits[2] = 423;
  decimal_1.bits[3] = 786432;

  decimal_2.bits[0] = 1658453339;
  decimal_2.bits[1] = 2896612263;
  decimal_2.bits[2] = 67010;
  decimal_2.bits[3] = 786432;

  s21_decimal true_result;
  s21_decimal_null(&true_result);
  true_result.bits[0] = 2998137797;
  true_result.bits[1] = 614149364;
  true_result.bits[2] = 3426771;
  true_result.bits[3] = 1835008;

  int status = s21_div(decimal_1, decimal_2, &result);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(result, true_result));
  ck_assert_int_eq(status, true_status);
}

Suite *test_div(void) {
  Suite *s = suite_create("\033[41m-=test_div=-\033[0m");
  TCase *tc = tcase_create("sub_tc");

  tcase_add_test(tc, test_div_1);
  tcase_add_test(tc, test_div_2);
  tcase_add_test(tc, test_div_3);
  tcase_add_test(tc, test_div_4);
  tcase_add_test(tc, test_div_5);
  tcase_add_test(tc, test_div_6);
  tcase_add_test(tc, test_div_7);
  tcase_add_test(tc, test_div_8);
  tcase_add_test(tc, test_div_9);
  tcase_add_test(tc, test_div_10);
  tcase_add_test(tc, test_div_11);
  tcase_add_test(tc, test_div_12);
  suite_add_tcase(s, tc);
  return s;
}
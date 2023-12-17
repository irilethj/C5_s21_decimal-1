#include "s21_test.h"

START_TEST(test_sub_1) {
  s21_decimal decimal_1;
  s21_decimal decimal_2;
  s21_decimal result;
  s21_decimal_null(&decimal_1);
  s21_decimal_null(&decimal_2);
  s21_decimal_null(&result);

  decimal_1.bits[0] = 532167;

  decimal_2.bits[0] = 123456;

  s21_decimal true_result;
  s21_decimal_null(&true_result);
  true_result.bits[0] = 408711;

  int status = s21_sub(decimal_1, decimal_2, &result);

  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(result, true_result));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_sub_2) {
  s21_decimal decimal_1;
  s21_decimal decimal_2;
  s21_decimal result;
  s21_decimal_null(&decimal_1);
  s21_decimal_null(&decimal_2);
  decimal_1.bits[0] = 123456;
  decimal_2.bits[0] = 532167;

  s21_decimal true_result;
  s21_decimal_null(&true_result);
  true_result.bits[0] = 408711;
  true_result.bits[3] = MINUS;

  int status = s21_sub(decimal_1, decimal_2, &result);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(result, true_result));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_sub_3) {
  s21_decimal decimal_1;
  s21_decimal decimal_2;
  s21_decimal result;
  s21_decimal_null(&decimal_1);
  s21_decimal_null(&decimal_2);
  s21_decimal_null(&result);

  decimal_1.bits[0] = 532167;
  decimal_1.bits[3] = MINUS;

  decimal_2.bits[0] = 123456;
  decimal_2.bits[3] = MINUS;

  s21_decimal true_result;
  s21_decimal_null(&true_result);
  true_result.bits[0] = 408711;
  true_result.bits[3] = MINUS;
  int status = s21_sub(decimal_1, decimal_2, &result);

  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(result, true_result));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_sub_4) {
  s21_decimal decimal_1;
  s21_decimal decimal_2;
  s21_decimal result;
  s21_decimal_null(&decimal_1);
  s21_decimal_null(&decimal_2);

  decimal_1.bits[0] = 61287;
  decimal_1.bits[3] = MINUS;

  decimal_2.bits[0] = 234787;
  decimal_2.bits[3] = MINUS;

  s21_decimal true_result;
  s21_decimal_null(&true_result);
  true_result.bits[0] = 173500;

  int status = s21_sub(decimal_1, decimal_2, &result);

  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(result, true_result));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_sub_5) {
  s21_decimal decimal_1;
  s21_decimal decimal_2;
  s21_decimal result;
  s21_decimal_null(&decimal_1);
  s21_decimal_null(&decimal_2);
  s21_decimal_null(&result);

  decimal_1.bits[0] = 532167;
  decimal_1.bits[3] = 196608;

  decimal_2.bits[0] = 1236;
  decimal_2.bits[3] = 983040;

  s21_decimal true_result;
  s21_decimal_null(&true_result);
  true_result.bits[0] = 607087404;
  true_result.bits[1] = 123904785;
  true_result.bits[3] = 983040;
  int status = s21_sub(decimal_1, decimal_2, &result);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(result, true_result));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_sub_6) {
  s21_decimal decimal_1;
  s21_decimal decimal_2;
  s21_decimal result;
  s21_decimal_null(&decimal_1);
  s21_decimal_null(&decimal_2);
  s21_decimal_null(&result);

  decimal_1.bits[0] = 532167;
  decimal_1.bits[3] = 196608;

  decimal_2.bits[0] = 0;
  decimal_2.bits[3] = 0;

  s21_decimal true_result;
  s21_decimal_null(&true_result);
  true_result.bits[0] = 532167;
  true_result.bits[3] = 196608;

  int status = s21_sub(decimal_1, decimal_2, &result);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(result, true_result));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_sub_7) {
  s21_decimal decimal_1;
  s21_decimal decimal_2;
  s21_decimal result;
  s21_decimal_null(&decimal_1);
  s21_decimal_null(&decimal_2);

  decimal_1.bits[0] = 2361234;
  decimal_1.bits[3] = MINUS;

  decimal_2.bits[0] = 48695;

  s21_decimal true_result;
  s21_decimal_null(&true_result);
  true_result.bits[0] = 2409929;
  true_result.bits[3] = MINUS;

  int status = s21_sub(decimal_1, decimal_2, &result);

  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(result, true_result));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_sub_8) {
  s21_decimal decimal_1;
  s21_decimal decimal_2;
  s21_decimal result;
  s21_decimal_null(&decimal_1);
  s21_decimal_null(&decimal_2);

  decimal_1.bits[0] = 6347852;

  decimal_2.bits[0] = 723184;
  decimal_2.bits[3] = MINUS;

  s21_decimal true_result;
  s21_decimal_null(&true_result);
  true_result.bits[0] = 7071036;

  int status = s21_sub(decimal_1, decimal_2, &result);

  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(result, true_result));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(test_sub_9) {
  s21_decimal decimal_1;
  s21_decimal decimal_2;
  s21_decimal result;
  s21_decimal_null(&decimal_1);
  s21_decimal_null(&decimal_2);

  decimal_1.bits[0] = 4294967295;
  decimal_1.bits[1] = 4294967295;
  decimal_1.bits[2] = 4294967295;

  decimal_2.bits[0] = 6;
  decimal_2.bits[1] = 0;
  decimal_2.bits[2] = 0;
  decimal_2.bits[3] = 65536;

  s21_decimal true_result;
  s21_decimal_null(&true_result);
  true_result.bits[0] = 4294967294;
  true_result.bits[1] = 4294967295;
  true_result.bits[2] = 4294967295;
  int status = s21_sub(decimal_1, decimal_2, &result);

  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(result, true_result));
  ck_assert_int_eq(status, true_status);
}
END_TEST

Suite *test_sub(void) {
  Suite *s = suite_create("\033[41m-=test_sub=-\033[0m");
  TCase *tc = tcase_create("sub_tc");

  tcase_add_test(tc, test_sub_1);
  tcase_add_test(tc, test_sub_2);
  tcase_add_test(tc, test_sub_3);
  tcase_add_test(tc, test_sub_4);
  tcase_add_test(tc, test_sub_5);
  tcase_add_test(tc, test_sub_6);
  tcase_add_test(tc, test_sub_7);
  tcase_add_test(tc, test_sub_8);
  tcase_add_test(tc, test_sub_9);
  suite_add_tcase(s, tc);
  return s;
}
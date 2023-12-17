#include "s21_test.h"

START_TEST(test_from_float_1) {
  s21_decimal val;
  s21_from_float_to_decimal(0.03F, &val);

  ck_assert_int_eq(val.bits[0], 3000000);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 524288);
  s21_from_float_to_decimal(127.1234F, &val);
  ck_assert_int_eq(val.bits[0], 1271234);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 262144);
}
END_TEST

START_TEST(test_from_float_2) {
  s21_decimal val;
  s21_from_float_to_decimal(22.14836E+03F, &val);
  ck_assert_int_eq(val.bits[0], 2214836);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 131072);
}
END_TEST

START_TEST(test_from_float_3) {
  s21_decimal val;
  s21_from_float_to_decimal(1.02E+09F, &val);
  ck_assert_int_eq(val.bits[0], 1020000000);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(test_from_float_4) {
  s21_decimal val;
  float a = 1.0F / 0.0F;
  int err_check = s21_from_float_to_decimal(a, &val);
  ck_assert_int_eq(err_check, 1);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(test_from_float_5) {
  s21_decimal val;
  float a = -1.0F / 0.0F;
  int err_check = s21_from_float_to_decimal(a, &val);
  ck_assert_int_eq(err_check, 1);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(test_from_float_6) {
  s21_decimal val;
  float a = NAN;
  int err_check = s21_from_float_to_decimal(a, &val);
  ck_assert_int_eq(err_check, 1);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(test_from_float_7) {
  s21_decimal val;
  s21_from_float_to_decimal(0.0F, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(test_from_float_8) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  long int c = 2147745792;
  src.bits[0] = 23450987;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = c;
  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -2345.0987);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_from_float_9) {
  s21_decimal dec;
  int result = 0;
  float number = 0.0;
  long int c = 0;
  dec.bits[0] = 23450987;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = c;
  result = s21_from_decimal_to_float(dec, &number);
  ck_assert_float_eq(number, 23450987.);
  ck_assert_int_eq(result, 0);
}
END_TEST

Suite *test_from_float(void) {
  Suite *s = suite_create("\033[42m-=test_from_float=-\033[0m");
  TCase *tc = tcase_create("add_tc");

  tcase_add_test(tc, test_from_float_1);
  tcase_add_test(tc, test_from_float_2);
  tcase_add_test(tc, test_from_float_3);
  tcase_add_test(tc, test_from_float_4);
  tcase_add_test(tc, test_from_float_5);
  tcase_add_test(tc, test_from_float_6);
  tcase_add_test(tc, test_from_float_7);
  tcase_add_test(tc, test_from_float_8);
  tcase_add_test(tc, test_from_float_9);

  suite_add_tcase(s, tc);
  return s;
}
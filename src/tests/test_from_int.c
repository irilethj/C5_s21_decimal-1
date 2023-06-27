#include "s21_test.h"

START_TEST(test_from_int_1) {
  s21_decimal result, origin;
  int src = 1;
  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  int result_error = 0;
  int my_error = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(test_from_int_2) {
  s21_decimal result, origin;
  int src = 0;
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  int result_error = 0;
  int my_error = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(test_from_int_3) {
  s21_decimal result, origin;
  int src = -1;
  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  int result_error = 0;
  int my_error = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(test_from_int_4) {
  s21_decimal result, origin;
  int src = 2147483647;
  origin.bits[0] = 0b01111111111111111111111111111111;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  int result_error = 0;
  int my_error = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(test_from_int_5) {
  s21_decimal result, origin;
  int src = -2147483647;
  origin.bits[0] = 0b01111111111111111111111111111111;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  int result_error = 0;
  int my_error = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(test_from_int_6) {
  s21_decimal result, origin;
  int src = -12345;
  origin.bits[0] = 0b00000000000000000011000000111001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  int result_error = 0;
  int my_error = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(test_from_int_7) {
  s21_decimal result, origin;
  int src = -12345;
  origin.bits[0] = 0b00000000000000000011000000111001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  int result_error = 0;
  int my_error = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(test_from_int_8) {
  s21_decimal result, origin;
  int src = 0;
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  int result_error = 0;
  int my_error = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(test_from_int_9) {
  s21_decimal result, origin;
  int src = 45678;
  origin.bits[0] = 0b00000000000000001011001001101110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  int result_error = 0;
  int my_error = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(test_from_int_10) {
  s21_decimal result, origin;
  int src = -45678;
  origin.bits[0] = 0b00000000000000001011001001101110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  int result_error = 0;
  int my_error = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(test_from_int_11) {
  s21_decimal result, origin;
  int src = 5555555;
  origin.bits[0] = 0b00000000010101001100010101100011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  int result_error = 0;
  int my_error = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(test_from_int_12) {
  s21_decimal result, origin;
  int src = -5555555;
  origin.bits[0] = 0b00000000010101001100010101100011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  int result_error = 0;
  int my_error = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(test_from_int_13) {
  s21_decimal result, origin;
  int src = 127;
  origin.bits[0] = 0b00000000000000000000000001111111;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  int result_error = 0;
  int my_error = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(test_from_int_14) {
  s21_decimal result, origin;
  int src = -127;
  origin.bits[0] = 0b00000000000000000000000001111111;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  int result_error = 0;
  int my_error = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(test_from_int_15) {
  s21_decimal result, origin;
  int src = 34567898;
  origin.bits[0] = 0b00000010000011110111011011011010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  int result_error = 0;
  int my_error = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(test_from_int_16) {
  s21_decimal result, origin;
  int src = -34567898;
  origin.bits[0] = 0b00000010000011110111011011011010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  int result_error = 0;
  int my_error = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(test_from_int_17) {
  s21_decimal result, origin;
  int src = 999;
  origin.bits[0] = 0b00000000000000000000001111100111;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  int result_error = 0;
  int my_error = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(test_from_int_18) {
  s21_decimal result, origin;
  int src = -999;
  origin.bits[0] = 0b00000000000000000000001111100111;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  int result_error = 0;
  int my_error = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(test_from_int_19) {
  s21_decimal result, origin;
  int src = -3254754;
  origin.bits[0] = 0b00000000001100011010100111100010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  int result_error = 0;
  int my_error = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(test_from_int_20) {
  s21_decimal result, origin;
  int src = 3436425;
  origin.bits[0] = 0b00000000001101000110111110001001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  int result_error = 0;
  int my_error = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

START_TEST(test_from_int_21) {
  s21_decimal result, origin;
  int src = 222222222;
  origin.bits[0] = 0b00001101001111101101011110001110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  int result_error = 0;
  int my_error = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(result_error, my_error);
}
END_TEST

Suite *test_from_int(void) {
  Suite *s = suite_create("\033[42m-=test_from_int=-\033[0m");
  TCase *tc = tcase_create("add_tc");

  tcase_add_test(tc, test_from_int_1);
  tcase_add_test(tc, test_from_int_2);
  tcase_add_test(tc, test_from_int_3);
  tcase_add_test(tc, test_from_int_4);
  tcase_add_test(tc, test_from_int_5);
  tcase_add_test(tc, test_from_int_6);
  tcase_add_test(tc, test_from_int_7);
  tcase_add_test(tc, test_from_int_8);
  tcase_add_test(tc, test_from_int_9);
  tcase_add_test(tc, test_from_int_10);
  tcase_add_test(tc, test_from_int_11);
  tcase_add_test(tc, test_from_int_12);
  tcase_add_test(tc, test_from_int_13);
  tcase_add_test(tc, test_from_int_14);
  tcase_add_test(tc, test_from_int_15);
  tcase_add_test(tc, test_from_int_16);
  tcase_add_test(tc, test_from_int_17);
  tcase_add_test(tc, test_from_int_18);
  tcase_add_test(tc, test_from_int_19);
  tcase_add_test(tc, test_from_int_20);
  tcase_add_test(tc, test_from_int_21);

  suite_add_tcase(s, tc);
  return s;
}
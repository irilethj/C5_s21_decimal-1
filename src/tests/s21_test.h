#ifndef S21_TEST_H
#define S21_TEST_H

#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_decimal.h"

Suite *test_from_dec_to_int(void);
Suite *test_from_dec_to_float(void);
Suite *test_from_float(void);
Suite *test_add(void);
Suite *test_from_int(void);
Suite *test_truncate(void);
Suite *test_negate(void);
Suite *test_floor(void);
Suite *test_round(void);
Suite *test_is_less(void);
Suite *test_is_less_or_equal(void);
Suite *test_is_greater(void);
Suite *test_is_greater_or_equal(void);
Suite *test_is_equal(void);
Suite *test_is_not_equal(void);
Suite *test_sub(void);
Suite *test_mul(void);
Suite *test_div(void);

#endif
#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <limits.h>
#include <math.h>
#include <stdio.h>

#define OK 0
#define CONVERTATION_ERROR 1
#define s21_TRUE 1
#define s21_FALSE 0
#define MAX_DECIMAL 79228162514264337593543950335
#define MIN_DECIMAL 1e-28
#define MAX_DEC powf(2.0f, 96.0f) - 1.0
#define MIN_DEC -powf(2.0f, 96.0f) + 1.0
#define MINUS_SIGN 2147483648

// structs

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[8];
} s21_big_decimal;

// compairs

int s21_is_less(s21_decimal value1, s21_decimal value2);
int s21_is_less_or_equal(s21_decimal value1, s21_decimal value2);
int s21_is_greater(s21_decimal value1, s21_decimal value2);
int s21_is_greater_or_equal(s21_decimal value1, s21_decimal value2);
int s21_is_equal(s21_decimal value1, s21_decimal value2);
int s21_is_not_equal(s21_decimal value1, s21_decimal value2);

// another funcs

int s21_floor(s21_decimal value, s21_decimal *result);  // --
int s21_round(s21_decimal value, s21_decimal *result);  // --
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// arithmetic

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// convertation funcs

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// sub funcs

int s21_last_bits(int sign, int pow);
int s21_normalize(s21_decimal *value_1, s21_decimal *value_2);
int s21_dec_mult_ten(s21_decimal value_1, s21_decimal *res);
int s21_substruction(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result);
int s21_check_sign(s21_decimal value1);
int s21_check_is_zero(s21_decimal);
int s21_get_bit(s21_decimal *count, int index);
int s21_get_pow(s21_decimal bit);
int s21_find_float_exp(float count);
int s21_adding(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_set_zero_mantisa(s21_big_decimal *value);
void s21_set_sign_bit(s21_big_decimal *value, int index, int var);
void s21_transf_to_big(s21_big_decimal *bvalue1, s21_decimal value1);
void s21_set_bit(s21_decimal *count, int index, int bit);
void s21_set_sign(s21_decimal *count, int sign);
void s21_set_pow(s21_decimal *count, int pow);
void s21_set_bpow(s21_big_decimal *count, int pow);
void s21_decimal_null(s21_decimal *count);
void s21_division_by_10(s21_decimal *count);
void s21_shift_decimal_left(s21_decimal *count);
void s21_shift_decimal_right(s21_decimal *count);
void s21_bdecimal_null(s21_big_decimal *value);

#endif
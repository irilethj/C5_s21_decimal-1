#ifndef S21_DECIMAL
#define S21_DECIMAL

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MINUS 0b10000000000000000000000000000000

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {  //    bits[7]         bits[6]    bits[5]     bits[4]   bits[3]
                  //    bits[2]   bits[1]     bits[0]
  unsigned int bits[8];  // {{sign and scail}, {32 нуля}, {32 нуля}, {32 нуля},
                         // {32 нуля}, {32 нуля}, {32 нуля}, {32 нуля}}
} s21_big_decimal;

// help functions
int s21_num_length(long long int int_part);
void s21_dec_mult_ten(s21_decimal* value);
void s21_normalize(s21_decimal* value_1, s21_decimal* value_2);
void s21_add_for_compare(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal* result);
int s21_shift_decimal_left(s21_decimal* count);
int s21_compare_mantissa(s21_decimal value_1, s21_decimal value_2,
                         int common_sign);
int s21_compare(s21_decimal value_1, s21_decimal value_2);
void s21_decimal_null(s21_decimal* src);
void s21_big_decimal_null(s21_big_decimal* src);
int s21_get_bit(s21_decimal dst, int index);
int s21_get_bit_int(int x, int index);
void s21_set_bit(s21_decimal* dst, int index, int bit);
void s21_set_scale(s21_big_decimal* dst, int scale);
int s21_get_scale(s21_decimal src);
int s21_bget_scale(s21_big_decimal src);
double s21_convert_mantissa_to_double(s21_decimal dst);
// void s21_print_decimal(s21_decimal src);
//   void s21_print_dec_int(s21_decimal src);
void s21_shift_bdecimal_right(s21_big_decimal* count);
void s21_subtraction(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal* result);
// void s21_print_int(int x);
void s21_dopol_code(s21_big_decimal value, s21_big_decimal* result);
int s21_compare_big_mantissa(s21_big_decimal value_1, s21_big_decimal value_2);
int s21_shift_big_decimal_left(s21_big_decimal* count);
void s21_bset_bit(s21_big_decimal* dst, int index, int bit);
int s21_dischage(s21_big_decimal* divide_by_10, s21_big_decimal* get);
int s21_division_by_ten(s21_big_decimal value, s21_big_decimal* int_part);
// void s21_print_bdec_int(s21_big_decimal src);
void s21_move_to_big(s21_big_decimal* big_value, s21_decimal value);
// void s21_print_big_decimal(s21_big_decimal src);
int s21_bget_bit(s21_big_decimal dst, int index);
void s21_add_for_division(s21_big_decimal value_1, s21_big_decimal value_2,
                          s21_big_decimal* result);
void s21_bnormalize(s21_big_decimal* value_1, s21_big_decimal* value_2);
void s21_bdec_mult_ten(s21_big_decimal* value);
void s21_move_back(s21_big_decimal big_value, s21_decimal* value);
int s21_check_and_transfer(s21_big_decimal value, s21_decimal* result);
int s21_check_overflow(s21_big_decimal value);
int s21_sign_result(s21_decimal value_1, s21_decimal value_2);
void s21_division(s21_big_decimal value_1, s21_big_decimal value_2,
                  s21_big_decimal* int_part, s21_big_decimal* remaind);
void s21_mult(s21_big_decimal value_1, s21_big_decimal value_2,
              s21_big_decimal* result);
int s21_null_check(s21_decimal value);
int s21_bnull_check(s21_big_decimal value);
int s21_dis(s21_big_decimal* dividend, s21_big_decimal divider,
            s21_big_decimal* get);
void s21_banking_rounding(s21_big_decimal* value, int remaind,
                          int prev_remaind);

// convertors
int s21_from_int_to_decimal(int src, s21_decimal* dst);
int s21_from_decimal_to_int(s21_decimal src, int* dst);
int s21_from_float_to_decimal(float src, s21_decimal* dst);
int s21_from_decimal_to_float(s21_decimal src, float* dst);

// another functions
int s21_truncate(s21_decimal value, s21_decimal* result);
int s21_negate(s21_decimal value, s21_decimal* result);
int s21_floor(s21_decimal value, s21_decimal* result);
int s21_round(s21_decimal value, s21_decimal* result);

// comparsions operators
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
void s21_dec_mult_ten(s21_decimal* value);

// arithmetic operators
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);

#endif

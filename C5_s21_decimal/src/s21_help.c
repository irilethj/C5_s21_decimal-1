#include "s21_decimal.h"

void s21_bdecimal_null(s21_big_decimal* value) {
  for (int i = 0; i < 8; i++) {
    value->bits[i] = 0;
  }
}

int s21_check_is_zero(s21_decimal value) {
  int res =
      (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0) ? 1 : 0;

  return res;
}

int s21_check_sign(s21_decimal value1) {
  return (value1.bits[3] & (1 << 31)) >> 31;
}

void s21_decimal_null(s21_decimal* count) {
  for (int i = 0; i < 4; i++) count->bits[i] = 0;
}

int s21_get_bit(s21_decimal* count, int index) {
  int num_bit = index / 32;
  int pos = index % 32;
  return (count->bits[num_bit] & (1 << pos)) >> pos;
}

int s21_get_pow(s21_decimal bit) {
  int power = 0, n = 0;
  for (int i = 16; i <= 23; i++) {
    power += pow(2, n) * s21_get_bit(&bit, i + 96);
    n++;
  }
  return power;
}

void s21_set_bit(s21_decimal* count, int index, int bit) {
  int num_bit = index / 32;
  int pos = index % 32;
  if (bit)
    count->bits[num_bit] |= (1 << pos);
  else
    count->bits[num_bit] &= ~(1 << pos);
}

void s21_set_pow(s21_decimal* count, int pow) {
  for (int i = 15; i <= 23; i++) {
    s21_set_bit(count, i + 97, pow & (1 << (i - 15)));
  }
}

void s21_set_sign(s21_decimal* count, int sign) {
  if (sign)
    count->bits[3] |= (1 << 31);
  else
    count->bits[3] &= ~(1 << 31);
}

void s21_shift_decimal_left(s21_decimal* count) {
  s21_decimal copy = {0};
  for (int i = 1; i <= 96; i++)
    if (s21_get_bit(count, i - 1)) s21_set_bit(&copy, i, 1);
  count->bits[0] = copy.bits[0];
  count->bits[1] = copy.bits[1];
  count->bits[2] = copy.bits[2];
}

void s21_shift_decimal_right(s21_decimal* count) {
  s21_decimal copy = {0};
  for (int i = 0; i <= 96; i++)
    if (s21_get_bit(count, i + 1)) s21_set_bit(&copy, i, 1);
  count->bits[0] = copy.bits[0];
  count->bits[1] = copy.bits[1];
  count->bits[2] = copy.bits[2];
}

void s21_transf_to_big(s21_big_decimal* bvalue1, s21_decimal value1) {
  for (int t = 0; t < 3; t++) {
    bvalue1->bits[t] = value1.bits[t];
  }
  bvalue1->bits[7] = value1.bits[3];
}

void s21_division_by_10(s21_decimal* count) {
  int exp = -1;
  int pow_count = s21_get_pow(*count);
  int sign = s21_get_bit(count, 127);
  s21_decimal sum = {0};
  s21_decimal ten = {0};
  s21_from_int_to_decimal(10, &ten);
  if (sign) s21_set_bit(count, 127, 0);
  s21_set_pow(count, 0);
  while (s21_is_greater_or_equal(*count, ten)) {
    s21_from_int_to_decimal(10, &ten);
    do {
      if (exp != -1) s21_shift_decimal_left(&ten);
      exp++;
    } while (s21_is_less_or_equal(ten, *count) && exp <= 91);
    s21_decimal slag = {0};
    s21_set_bit(&slag, exp - 1, 1);
    s21_add(slag, sum, &sum);
    s21_shift_decimal_right(&ten);
    s21_sub(*count, ten, count);
    exp = -1;
    s21_from_int_to_decimal(10, &ten);
  }
  if (sign) s21_set_bit(&sum, 127, 1);
  if (pow_count != 0) s21_set_pow(&sum, pow_count - 1);
  count->bits[0] = sum.bits[0];
  count->bits[1] = sum.bits[1];
  count->bits[2] = sum.bits[2];
  count->bits[3] = sum.bits[3];
}

int s21_dec_mult_ten(s21_decimal value_1, s21_decimal* res) {
  int arr2[100] = {0}, arr4[100] = {0};
  int error = 0;
  int power = s21_get_pow(value_1);
  int sign = s21_get_bit(&value_1, 127);
  s21_decimal_null(res);
  for (int j = 3; j <= 99; j++) {
    arr2[j - 2] = s21_get_bit(&value_1, j - 3);
    arr4[j] = s21_get_bit(&value_1, j - 3);
  }
  int occupy = 0;
  for (int j = 1; j <= 95; j++) {
    if (arr2[j] + arr4[j] + occupy == 1) {
      s21_set_bit(res, j, 1);
      occupy = 0;
    } else if (arr2[j] + arr4[j] + occupy == 2)
      occupy = 1;
    else if (arr2[j] + arr4[j] + occupy == 3) {
      s21_set_bit(res, j, 1);
      occupy = 1;
    } else
      occupy = 0;
  }
  s21_set_sign(res, sign);
  s21_set_pow(res, power + 1);
  if (occupy && s21_get_bit(&value_1, 127))
    error = 2;
  else if (occupy)
    error = 1;
  return error;
}

int s21_normalize(s21_decimal* value_1, s21_decimal* value_2) {
  int power_1 = s21_get_pow(*value_1);
  int power_2 = s21_get_pow(*value_2);
  s21_decimal copy_1 = *value_1;
  s21_decimal copy_2 = *value_2;
  int error = 0;
  while (power_1 != power_2 && error == 0) {
    copy_1 = *value_1;
    copy_2 = *value_2;
    if (power_1 > power_2 && power_2 < 28) {
      error = s21_dec_mult_ten(*value_2, value_2);
      power_2++;
    } else if (power_1 < power_2 && power_1 < 28) {
      error = s21_dec_mult_ten(*value_1, value_1);
      power_1++;
    } else if (power_2 > 28) {
      s21_division_by_10(value_2);
      power_2--;
    } else if (power_1 > 28) {
      s21_division_by_10(value_1);
      power_1--;
    }
  }
  if (error && power_1 > 3 && power_2 > 3) {
    *value_1 = copy_1;
    *value_2 = copy_2;
    power_1 = s21_get_pow(*value_1);
    power_2 = s21_get_pow(*value_2);
    while (power_1 != power_2) {
      if (power_1 < power_2) {
        s21_division_by_10(value_2);
        power_2--;
      } else {
        s21_division_by_10(value_1);
        power_1--;
      }
    }
    error = 0;
  }
  return error;
}

#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  s21_decimal_null(dst);
  int status = 0;
  if (isinf(src) || isnan(src)) {
    status = 1;
  } else {
    if (src != 0) {
      int exp = 0, power = 0;
      float copy = 0;
      // double mant = 0;
      int sign = (*(int *)&src & (1 << 31)) >> 31;
      double copy_src = (double)fabs(src);
      for (; power < 28 && (int)copy_src / (int)pow(2, 21) == 0;
           copy_src *= 10, power++) {
      }
      exp = s21_find_float_exp(src);
      /*     n = exp - 23;
           for(int i = 0; i <= 22; i++){
             mant += pow(2, n) * ((*(int*)&src & (1 << i)) >> i);
             n++;
           }
           mant += pow(2, exp);
           printf("%f\n", mant); */
      s21_set_sign(dst, sign);
      copy_src = (float)round(copy_src);
      for (; fmod(copy_src, 10) == 0 && power > 0; power--, copy_src /= 10) {
      }
      copy = copy_src;
      exp = s21_find_float_exp(copy);
      s21_set_bit(dst, exp, 1);
      for (int i = exp - 1, j = 22; j >= 0; i--, j--)
        if ((*(int *)&copy & (1 << j)) != 0) s21_set_bit(dst, i, 1);
      s21_set_pow(dst, power);
      // double bit = floor(log2l(mant)) + 1;
      /*  for(int i = 0; i < bit; i++){
         s21_set_bit(dst, i, ((*(int*)&mant & (1 << i)) >> i)); */
      //}
    }
  }
  return status;
}

int s21_find_float_exp(float count) {
  int n = 7, exp = 0;
  for (int i = 30; i >= 23; i--) {
    exp += pow(2, n) * ((*(int *)&count & (1 << i)) >> i);
    n--;
  }
  exp -= 127;
  return exp;
}

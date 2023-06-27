CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11 -lm
STATIC = ar rcs
TESTFLAGC = -lcheck

GCOVFLAGS = -fprofile-arcs -ftest-coverage
SOURCES_ALL:=$(wildcard *.c ./tests/*.c)
SOURCES_FUN:=$(shell find . -not -name "test*.c" -not -name "s21_test*.c" -name "*.c")
UNAME:=$(shell uname -s)

ifeq ($(UNAME),Linux)
	LDFLAGS=-lcheck -lsubunit -lrt -lpthread -lm
	OPEN_CM=xdg-open
endif
ifeq ($(UNAME),Darwin)
	LDFLAGS=-lcheck
	OPEN_CM=open
endif

all: clean s21_decimal.a test gcov_report

s21_arithmetic_operators.o: s21_arithmetic_operators.c
	$(CC) $(CFLAGS) -c s21_arithmetic_operators.c -lm

s21_comparison_operators.o: s21_comparison_operators.c
	$(CC) $(CFLAGS) -c s21_comparison_operators.c -lm

s21_convertors.o: s21_convertors.c
	$(CC) $(CFLAGS) -c s21_convertors.c -lm

s21_help_functions.o: s21_help_functions.c
	$(CC) $(CFLAGS) -c s21_help_functions.c -lm

s21_other.o: s21_other.c
	$(CC) $(CFLAGS) -c s21_other.c -lm

s21_decimal.a: s21_arithmetic_operators.o s21_comparison_operators.o s21_convertors.o s21_help_functions.o s21_other.o
	$(STATIC) s21_decimal.a s21_arithmetic_operators.o s21_comparison_operators.o s21_convertors.o s21_help_functions.o s21_other.o
	ranlib s21_decimal.a

test: s21_decimal.a s21_test.o test_add.o test_from_dec_to_int.o test_from_dec_to_float.o test_from_float.o test_from_int.o test_truncate.o test_negate.o test_floor.o test_round.o test_is_less.o test_is_less_or_equal.o test_is_greater.o test_is_greater_or_equal.o test_is_equal.o test_is_not_equal.o test_sub.o test_mul.o test_div.o
	$(CC) s21_test.o test_add.o test_from_dec_to_int.o test_from_dec_to_float.o test_from_float.o test_from_int.o test_truncate.o test_negate.o test_floor.o test_round.o test_is_less.o test_is_less_or_equal.o test_is_greater.o test_is_greater_or_equal.o test_is_equal.o test_is_not_equal.o test_sub.o test_mul.o test_div.o -L. s21_decimal.a $(LDFLAGS) -o test
#	./test

s21_test.o: ./tests/s21_test.c
	$(CC) $(CFLAGS) -c $^ -o $@ -lm

test_add.o: ./tests/test_add.c
	$(CC) $(CFLAGS) -c $^ -o $@ -lm

test_from_dec_to_int.o: ./tests/test_from_dec_to_int.c
	$(CC) $(CFLAGS) -c $^ -o $@ -lm

test_from_dec_to_float.o: ./tests/test_from_dec_to_float.c
	$(CC) $(CFLAGS) -c $^ -o $@ -lm

test_from_float.o: ./tests/test_from_float.c
	$(CC) $(CFLAGS) -c $^ -o $@ -lm

test_from_int.o: ./tests/test_from_int.c
	$(CC) $(CFLAGS) -c $^ -o $@ -lm

test_truncate.o: ./tests/test_truncate.c
	$(CC) $(CFLAGS) -c $^ -o $@ -lm

test_negate.o: ./tests/test_negate.c
	$(CC) $(CFLAGS) -c $^ -o $@ -lm

test_floor.o: ./tests/test_floor.c
	$(CC) $(CFLAGS) -c $^ -o $@ -lm

test_round.o: ./tests/test_round.c
	$(CC) $(CFLAGS) -c $^ -o $@ -lm

test_is_less.o: ./tests/test_is_less.c
	$(CC) $(CFLAGS) -c $^ -o $@ -lm

test_is_less_or_equal.o: ./tests/test_is_less_or_equal.c
	$(CC) $(CFLAGS) -c $^ -o $@ -lm

test_is_greater.o: ./tests/test_is_greater.c
	$(CC) $(CFLAGS) -c $^ -o $@ -lm

test_is_greater_or_equal.o: ./tests/test_is_greater_or_equal.c
	$(CC) $(CFLAGS) -c $^ -o $@ -lm

test_is_equal.o: ./tests/test_is_equal.c
	$(CC) $(CFLAGS) -c $^ -o $@ -lm

test_is_not_equal.o: ./tests/test_is_not_equal.c
	$(CC) $(CFLAGS) -c $^ -o $@ -lm

test_sub.o: ./tests/test_sub.c
	$(CC) $(CFLAGS) -c $^ -o $@ -lm

test_mul.o: ./tests/test_mul.c
	$(CC) $(CFLAGS) -c $^ -o $@ -lm

test_div.o: ./tests/test_div.c
	$(CC) $(CFLAGS) -c $^ -o $@ -lm

gcov_report: test
	$(CC) $(GCOVFLAGS) $(SOURCES_ALL) $(LDFLAGS) -o report.out
	./report.out
	gcov -f $(SOURCES_FUN)
	lcov -t "gcov_report" -o Coverage_Report.info -c -d .
	genhtml -o ./report Coverage_Report.info
	$(OPEN_CM) ./report/index-sort-f.html

libs: s21_string.a

rebuild: 
	make clean all

clean:
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.out
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./test && rm -rf ./gcov_report
	-rm -rf ./report/

#.PHONY: all clean test

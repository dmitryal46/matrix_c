PHONY: s21_matrix.a

CC=gcc -std=c11
CFLAGS=-Wall -Wextra -Werror
FLAG_COV=--coverage
FUNC_TESTS_C=tests/*_test.c
VALGRIND_FLAGS=--tool=memcheck --track-origins=yes

OS=$(shell uname -s)

ifeq ($(OS),Linux)
	TEST_LIBS=-lcheck -lsubunit -pthread -lrt -lm
else
	TEST_LIBS=-lcheck
endif

all: clean test s21_matrix.a gcov_report 

s21_matrix.a: *.c
	$(CC) $(CFLAGS) -c $^
	ar rc $@ *.o
	ranlib $@

test: clean
	$(CC) $(CFLAGS) -o s21_matrix tests/main.c $(FUNC_TESTS_C) *.c $(FLAG_COV) $(TEST_LIBS)
	./s21_matrix

valgrind: clean
	$(CC) $(CFLAGS) -o s21_matrix tests/main.c $(FUNC_TESTS_C) -g -O0 *.c $(TEST_LIBS)
	valgrind $(VALGRIND_FLAGS) ./s21_matrix

gcov_report: test 
	gcov ./s21_matrix
	lcov -c -d . -o gcov.info
	genhtml gcov.info -o gcov_report
	open gcov_report/index.html

clean:
	rm -rf gcov_report/
	rm -f *.info s21_matrix
	rm -f *.gcda *.gcno *.gcov *.gch *.o *.a *.out


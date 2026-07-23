CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

# Флаги для библиотеки Check
LIBS = -lcheck -lm -lpthread -lrt -lsubunit

SRC = s21_string.c
OBJ = $(SRC:.c=.o)

TEST_SRC = tests/s21_test.c
TEST_OBJ = tests/s21_test.o

all: s21_string.a

s21_string.a: $(OBJ)
	ar rcs s21_string.a $(OBJ)
	ranlib s21_string.a

%.o: %.c s21_string.h
	$(CC) $(CFLAGS) -c $< -o $@

test: s21_string.a $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) s21_string.a -o unit_tests $(LIBS)
	./unit_tests

gcov_report: clean
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(SRC) $(TEST_SRC) -o gcov_test $(LIBS)
	./gcov_test
	lcov -t "gcov_report" -o gcov_test.info -c -d .
	genhtml -o report gcov_test.info
	@echo "Отчет готов. Откройте report/index.html в браузере."

clean:
	rm -rf *.o *.a *.gcda *.gcno *.info unit_tests gcov_test report

.PHONY: all test gcov_report clean
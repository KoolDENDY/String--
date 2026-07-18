CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror
LDFLAGS = -lm

SRC_DIR = src
TEST_DIR = tests

SRC = $(SRC_DIR)/s21_sprintf.c $(SRC_DIR)/s21_sprintf_utils.c
OBJ = $(SRC:.c=.o)

LIB = s21_string.a

TEST_SRC = $(TEST_DIR)/test_s21_sprintf.c
TEST_BIN = test_s21_sprintf
CHECK_FLAGS = $(shell pkg-config --cflags --libs check)

GCOV_DIR = gcov_build

.PHONY: all clean test gcov_report rebuild

all: $(LIB)

$(LIB): $(OBJ)
	ar rcs $(LIB) $(OBJ)
	ranlib $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(SRC) $(TEST_SRC)
	$(CC) $(CFLAGS) -o $(TEST_BIN) $(SRC) $(TEST_SRC) $(CHECK_FLAGS) $(LDFLAGS)

gcov_report:
	@mkdir -p $(GCOV_DIR)
	$(CC) $(CFLAGS) --coverage -o $(GCOV_DIR)/$(TEST_BIN) $(SRC) $(TEST_SRC) $(CHECK_FLAGS) $(LDFLAGS)
	./$(GCOV_DIR)/$(TEST_BIN)
	mv *.gcda *.gcno $(GCOV_DIR) 2>/dev/null || true
	lcov -t "s21_sprintf" -o $(GCOV_DIR)/coverage.info -c -d $(GCOV_DIR) \
		--include "*/s21_sprintf.c" --include "*/s21_sprintf_utils.c"
	genhtml -o $(GCOV_DIR)/html $(GCOV_DIR)/coverage.info
	@echo "Coverage report: $(GCOV_DIR)/html/index.html"

clean:
	rm -f $(OBJ) $(LIB) $(TEST_BIN)
	rm -rf $(GCOV_DIR)
	rm -f *.gcda *.gcno *.gcov

rebuild: clean all

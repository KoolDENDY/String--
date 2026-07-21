CC = gcc
CFLAGS = -Wall -Wextra -std=c11 
# без веррор потмоу что ругается  на strncat и на strncpy

all: test

test:
	$(CC) $(CFLAGS) s21_memory.c s21_string.c tests/test_block2.c -o test
	./test

clean:
	rm -f test
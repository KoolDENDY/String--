#ifndef S21_STRING_H
#define S21_STRING_H

#include <stddef.h>  // для size_t
#include <stdlib.h>  // для NULL

// блок 2: функции памяти и строк
void *s21_memchr(const void *s, int c, size_t n);
int s21_memcmp(const void *s1, const void *s2, size_t n);
void *s21_memcpy(void *dest, const void *src, size_t n);
void *s21_memset(void *s, int c, size_t n);
size_t s21_strlen(const char *s);
char *s21_strncpy(char *dest, const char *src, size_t n);
char *s21_strncat(char *dest, const char *src, size_t n);
int s21_strncmp(const char *s1, const char *s2, size_t n);

#endif
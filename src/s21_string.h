#ifndef S21_STRING_H
#define S21_STRING_H

#define S21_NULL ((void *)0)
typedef unsigned long s21_size_t;

void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

#endif
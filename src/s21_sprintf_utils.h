#ifndef S21_SPRINTF_UTILS_H
#define S21_SPRINTF_UTILS_H

#include "s21_string.h"

s21_size_t s21_len(const char *str);

const char *s21_parse_spec(const char *format, va_list *args, s21_spec_t *spec);

int s21_fmt_char(char *dst, va_list *args, s21_spec_t spec);
int s21_fmt_string(char *dst, va_list *args, s21_spec_t spec);
int s21_fmt_signed(char *dst, va_list *args, s21_spec_t spec);
int s21_fmt_unsigned(char *dst, va_list *args, s21_spec_t spec, int base,
                      int upper_case);
int s21_fmt_float(char *dst, va_list *args, s21_spec_t spec, char conv);
int s21_fmt_pointer(char *dst, va_list *args, s21_spec_t spec);
int s21_fmt_percent(char *dst);

#endif 

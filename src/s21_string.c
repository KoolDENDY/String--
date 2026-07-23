#include "s21_string.h"

#include <stdlib.h>

void *s21_to_upper(const char *str) {
  if (str == S21_NULL) {
    return S21_NULL;
  }
  s21_size_t len = 0;
  while (str[len] != '\0') {
    len++;
  }
  char *result = (char *)malloc(len + 1);
  if (result == S21_NULL) {
    return S21_NULL;
  }
  for (s21_size_t i = 0; i <= len; i++) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      result[i] = str[i] - 32;
    } else {
      result[i] = str[i];
    }
  }
  return result;
}

void *s21_to_lower(const char *str) {
  if (str == S21_NULL) {
    return S21_NULL;
  }
  s21_size_t len = 0;
  while (str[len] != '\0') {
    len++;
  }
  char *result = (char *)malloc(len + 1);
  if (result == S21_NULL) {
    return S21_NULL;
  }
  for (s21_size_t i = 0; i <= len; i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      result[i] = str[i] + 32;
    } else {
      result[i] = str[i];
    }
  }
  return result;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (src == S21_NULL || str == S21_NULL) {
    return S21_NULL;
  }
  s21_size_t src_len = 0;
  while (src[src_len] != '\0') {
    src_len++;
  }
  if (start_index > src_len) {
    return S21_NULL;
  }
  s21_size_t str_len = 0;
  while (str[str_len] != '\0') {
    str_len++;
  }

  char *result = (char *)malloc(src_len + str_len + 1);
  if (result == S21_NULL) {
    return S21_NULL;
  }

  s21_size_t i = 0;
  for (; i < start_index; i++) {
    result[i] = src[i];
  }
  for (s21_size_t j = 0; j < str_len; j++, i++) {
    result[i] = str[j];
  }
  for (s21_size_t j = start_index; j < src_len; j++, i++) {
    result[i] = src[j];
  }
  result[i] = '\0';

  return result;
}

static int s21_is_trim_char(char c, const char *trim_chars) {
  int found = 0;
  for (int i = 0; trim_chars[i] != '\0' && !found; i++) {
    if (c == trim_chars[i]) {
      found = 1;
    }
  }
  return found;
}

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == S21_NULL) {
    return S21_NULL;
  }
  const char *default_trim = " \t\n\r\v\f";
  if (trim_chars == S21_NULL || trim_chars[0] == '\0') {
    trim_chars = default_trim;
  }

  s21_size_t start = 0;
  while (src[start] != '\0' && s21_is_trim_char(src[start], trim_chars)) {
    start++;
  }

  s21_size_t end = 0;
  while (src[end] != '\0') {
    end++;
  }

  if (end > 0) {
    end--;
  }

  while (end >= start && s21_is_trim_char(src[end], trim_chars)) {
    if (end == 0) break;
    end--;
  }

  char *result = S21_NULL;
  if (start > end) {
    result = (char *)malloc(1);
    if (result != S21_NULL) {
      result[0] = '\0';
    }
  } else {
    s21_size_t len = end - start + 1;
    result = (char *)malloc(len + 1);
    if (result != S21_NULL) {
      for (s21_size_t i = 0; i < len; i++) {
        result[i] = src[start + i];
      }
      result[len] = '\0';
    }
  }

  return result;
}
#include "s21_string.h"

// возвращает длину строки (без учета '\0')
size_t s21_strlen(const char *s) {
    if (s == NULL) return 0;
    
    size_t len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

// копирует не более n символов из src в dest
char *s21_strncpy(char *dest, const char *src, size_t n) {
    if (dest == NULL || src == NULL) return NULL;
    
    size_t i;
    // копируем символы из src в dest
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    // если src короче чем n, заполняем оставшиеся нулями
    for (; i < n; i++) {
        dest[i] = '\0';
    }
    
    return dest;
}

// добавляет не более n символов из src в конец dest
char *s21_strncat(char *dest, const char *src, size_t n) {
    if (dest == NULL || src == NULL) return NULL;
    
    size_t dest_len = s21_strlen(dest);
    size_t i;
    
    // копируем символы из src в конец dest
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[dest_len + i] = src[i];
    }
    // добавляем завершающий 0
    dest[dest_len + i] = '\0';
    
    return dest;
}

// сравнивает не более n символов двух строк
int s21_strncmp(const char *s1, const char *s2, size_t n) {
    if (s1 == NULL || s2 == NULL) return 0;
    
    for (size_t i = 0; i < n; i++) {
        if (s1[i] == '\0' || s2[i] == '\0') {
            return s1[i] - s2[i];
        }
        if (s1[i] != s2[i]) {
            return s1[i] - s2[i];
        }
    }
    
    return 0;
}
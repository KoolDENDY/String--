#include "s21_string.h"

// заполняет n байт памяти значением c
void *s21_memset(void *s, int c, size_t n) {
    if (s == NULL) return NULL;
    
    unsigned char *ptr = (unsigned char *)s;
    unsigned char value = (unsigned char)c;
    
    for (size_t i = 0; i < n; i++) {
        ptr[i] = value;
    }
    
    return s;
}

// копирует n байт из src в dest
void *s21_memcpy(void *dest, const void *src, size_t n) {
    if (dest == NULL || src == NULL) return NULL;
    
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    
    return dest;
}

// сравнивает n байт двух блоков памяти
int s21_memcmp(const void *s1, const void *s2, size_t n) {
    if (s1 == NULL || s2 == NULL) return 0;
    
    const unsigned char *p1 = (const unsigned char *)s1;
    const unsigned char *p2 = (const unsigned char *)s2;
    
    for (size_t i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] - p2[i];
        }
    }
    
    return 0;
}

// ищет первое вхождение символа c в n байтах памяти
void *s21_memchr(const void *s, int c, size_t n) {
    if (s == NULL) return NULL;
    
    const unsigned char *ptr = (const unsigned char *)s;
    unsigned char value = (unsigned char)c;
    
    for (size_t i = 0; i < n; i++) {
        if (ptr[i] == value) {
            return (void *)(ptr + i);
        }
    }
    
    return NULL;
}
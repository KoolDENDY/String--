#include <stdio.h>
#include <assert.h>
#include <string.h>  // для сравнения с оригиналом
#include "../s21_string.h"

// ============ Тесты для memset(НАДИПСИЧЕНО) ============
void test_memset() {
    char str1[20] = "Hello World";
    char str2[20] = "Hello World";
    
    s21_memset(str1, 'X', 5);
    memset(str2, 'X', 5);
    
    assert(strcmp(str1, str2) == 0);
    printf("✅ memset passed\n");
    
    // Тест с NULL
    assert(s21_memset(NULL, 'A', 10) == NULL);
}

// ============ Тесты для memcpy ============
void test_memcpy() {
    char src[] = "Hello World";
    char dest1[20] = {0};
    char dest2[20] = {0};
    
    s21_memcpy(dest1, src, 5);
    memcpy(dest2, src, 5);
    
    assert(memcmp(dest1, dest2, 20) == 0);
    printf("✅ memcpy passed\n");
}

// ============ Тесты для memcmp ============
void test_memcmp() {
    char str1[] = "Hello";
    char str2[] = "Hello";
    char str3[] = "Hella";
    
    assert(s21_memcmp(str1, str2, 5) == 0);
    assert(s21_memcmp(str1, str3, 5) > 0);
    assert(s21_memcmp(str3, str1, 5) < 0);
    printf("✅ memcmp passed\n");
}

// ============ Тесты для memchr ============
void test_memchr() {
    char str[] = "Hello World";
    
    char *res1 = (char *)s21_memchr(str, 'W', 11);
    char *res2 = (char *)memchr(str, 'W', 11);
    
    assert(res1 == res2);
    assert(s21_memchr(str, 'Z', 11) == NULL);
    printf("✅ memchr passed\n");
}

// ============ Тесты для strlen ============
void test_strlen() {
    assert(s21_strlen("Hello") == 5);
    assert(s21_strlen("") == 0);
    assert(s21_strlen("Hello World") == 11);
    assert(s21_strlen(NULL) == 0);
    printf("✅ strlen passed\n");
}

// ============ Тесты для strncpy ============
void test_strncpy() {
    char dest1[20] = {0};
    char dest2[20] = {0};
    
    s21_strncpy(dest1, "Hello World", 5);
    strncpy(dest2, "Hello World", 5);
    
    assert(strcmp(dest1, dest2) == 0);
    
    // Тест, когда src короче n
    char dest3[10] = {0};
    s21_strncpy(dest3, "Hi", 5);
    assert(dest3[0] == 'H');
    assert(dest3[1] == 'i');
    assert(dest3[2] == '\0');
    assert(dest3[3] == '\0');
    assert(dest3[4] == '\0');
    
    printf("✅ strncpy passed\n");
}

// ============ Тесты для strncat ============
void test_strncat() {
    char dest1[30] = "Hello";
    char dest2[30] = "Hello";
    
    s21_strncat(dest1, " World", 6);
    strncat(dest2, " World", 6);
    
    assert(strcmp(dest1, dest2) == 0);
    
    // Тест с ограничением
    char dest3[30] = "Hello";
    s21_strncat(dest3, " World", 3);
    assert(strcmp(dest3, "Hello Wo") == 0);
    
    printf("✅ strncat passed\n");
}

// ============ Тесты для strncmp ============
void test_strncmp() {
    assert(s21_strncmp("Hello", "Hello", 5) == 0);
    assert(s21_strncmp("Hello", "Hella", 4) == 0);
    assert(s21_strncmp("Hello", "Hella", 5) > 0);
    assert(s21_strncmp("Hella", "Hello", 5) < 0);
    assert(s21_strncmp("Hello", "Hello World", 5) == 0);
    assert(s21_strncmp(NULL, "Hello", 5) == 0);
    printf("✅ strncmp passed\n");
}

// ============ Все тесты ============
void run_all_tests() {
    printf("\n========== RUNNING TESTS ==========\n");
    
    test_memset();
    test_memcpy();
    test_memcmp();
    test_memchr();
    test_strlen();
    test_strncpy();
    test_strncat();
    test_strncmp();
    
    printf("\n========== ALL TESTS PASSED! ==========\n");
}

int main() {
    run_all_tests();
    return 0;
}
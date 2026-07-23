#include <check.h>
#include <stdlib.h>

#include "../s21_string.h"

START_TEST(test_to_upper_success) {
  char *res = s21_to_upper("hello 21!");
  ck_assert_str_eq(res, "HELLO 21!");
  free(res);
}
END_TEST

START_TEST(test_to_upper_null) {
  ck_assert_ptr_eq(s21_to_upper(S21_NULL), S21_NULL);
}
END_TEST

START_TEST(test_to_lower_success) {
  char *res = s21_to_lower("HELLO 21!");
  ck_assert_str_eq(res, "hello 21!");
  free(res);
}
END_TEST

START_TEST(test_to_lower_null) {
  ck_assert_ptr_eq(s21_to_lower(S21_NULL), S21_NULL);
}
END_TEST

START_TEST(test_insert_success) {
  char *res = s21_insert("School ", "21", 7);
  ck_assert_str_eq(res, "School 21");
  free(res);
}
END_TEST

START_TEST(test_insert_null_and_bounds) {
  ck_assert_ptr_eq(s21_insert(S21_NULL, "abc", 0), S21_NULL);
  ck_assert_ptr_eq(s21_insert("abc", S21_NULL, 0), S21_NULL);
  ck_assert_ptr_eq(s21_insert("abc", "def", 10), S21_NULL);
}
END_TEST

START_TEST(test_trim_success) {
  char *res = s21_trim("***Hello, world!***", "*");
  ck_assert_str_eq(res, "Hello, world!");
  free(res);
}
END_TEST

START_TEST(test_trim_null) {
  ck_assert_ptr_eq(s21_trim(S21_NULL, "*"), S21_NULL);
}
END_TEST

START_TEST(test_trim_default_spaces) {
  char *res = s21_trim("   Hello 21   ", S21_NULL);
  ck_assert_str_eq(res, "Hello 21");
  free(res);
}
END_TEST

// Добавляем тесты в test suite (набор тестов)

Suite *s21_string_suite(void) {
  Suite *suite = suite_create("s21_string");
  TCase *tcase_core = tcase_create("core");

  // Добавляем ВСЕ тесты сюда:
  tcase_add_test(tcase_core, test_to_upper_success);
  tcase_add_test(tcase_core, test_to_upper_null);
  tcase_add_test(tcase_core, test_to_lower_success);
  tcase_add_test(tcase_core, test_to_lower_null);
  tcase_add_test(tcase_core, test_insert_success);
  tcase_add_test(tcase_core, test_insert_null_and_bounds);
  tcase_add_test(tcase_core, test_trim_success);
  tcase_add_test(tcase_core, test_trim_null);
  tcase_add_test(tcase_core, test_trim_default_spaces);

  suite_add_tcase(suite, tcase_core);
  return suite;
}

int main(void) {
  Suite *suite = s21_string_suite();
  SRunner *runner = srunner_create(suite);

  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (number_failed == 0) ? 0 : 1;
}
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/s21_string.h"


#define ASSERT_SAME(...)                                     
  do {                                                        
    char s21_buf[1024] = {0};                                 
    char std_buf[1024] = {0};                                 
    int s21_len = s21_sprintf(s21_buf, __VA_ARGS__);           
    int std_len = sprintf(std_buf, __VA_ARGS__);                
    ck_assert_str_eq(s21_buf, std_buf);                       
    ck_assert_int_eq(s21_len, std_len);                       
  } while (0)



START_TEST(char_plain) { ASSERT_SAME("%c", 'A'); }
END_TEST

START_TEST(char_width_right) { ASSERT_SAME("[%5c]", 'x'); }
END_TEST

START_TEST(char_width_left) { ASSERT_SAME("[%-5c]", 'x'); }
END_TEST



START_TEST(string_plain) { ASSERT_SAME("%s", "hello world"); }
END_TEST

START_TEST(string_empty) { ASSERT_SAME("%s", ""); }
END_TEST

START_TEST(string_width_right) { ASSERT_SAME("[%10s]", "hi"); }
END_TEST

START_TEST(string_width_left) { ASSERT_SAME("[%-10s]", "hi"); }
END_TEST

START_TEST(string_precision) { ASSERT_SAME("%.3s", "hello"); }
END_TEST

START_TEST(string_width_and_precision) { ASSERT_SAME("[%10.3s]", "hello"); }
END_TEST



START_TEST(int_zero) { ASSERT_SAME("%d", 0); }
END_TEST

START_TEST(int_positive) { ASSERT_SAME("%d", 12345); }
END_TEST

START_TEST(int_negative) { ASSERT_SAME("%d", -12345); }
END_TEST

START_TEST(int_width) { ASSERT_SAME("[%8d]", 42); }
END_TEST

START_TEST(int_width_left) { ASSERT_SAME("[%-8d]", 42); }
END_TEST

START_TEST(int_zero_pad) { ASSERT_SAME("%06d", 42); }
END_TEST

START_TEST(int_zero_pad_negative) { ASSERT_SAME("%06d", -42); }
END_TEST

START_TEST(int_plus_flag) { ASSERT_SAME("%+d", 42); }
END_TEST

START_TEST(int_space_flag) { ASSERT_SAME("% d", 42); }
END_TEST

START_TEST(int_precision) { ASSERT_SAME("%.6d", 42); }
END_TEST

START_TEST(int_precision_zero_value) { ASSERT_SAME("%.0d", 0); }
END_TEST

START_TEST(int_width_and_precision) { ASSERT_SAME("%8.5d", 42); }
END_TEST

START_TEST(int_long_modifier) { ASSERT_SAME("%ld", 9876543210L); }
END_TEST

START_TEST(int_short_modifier) { ASSERT_SAME("%hd", (short)-1); }
END_TEST

START_TEST(int_alias_i) { ASSERT_SAME("%i", -777); }
END_TEST



START_TEST(uint_plain) { ASSERT_SAME("%u", 42u); }
END_TEST

START_TEST(uint_from_negative) { ASSERT_SAME("%u", -1); }
END_TEST

START_TEST(uint_width_zero_pad) { ASSERT_SAME("%08u", 42u); }
END_TEST



START_TEST(octal_plain) { ASSERT_SAME("%o", 8); }
END_TEST

START_TEST(octal_hash) { ASSERT_SAME("%#o", 8); }
END_TEST

START_TEST(octal_hash_zero) { ASSERT_SAME("%#o", 0); }
END_TEST



START_TEST(hex_lower) { ASSERT_SAME("%x", 255); }
END_TEST

START_TEST(hex_upper) { ASSERT_SAME("%X", 255); }
END_TEST

START_TEST(hex_hash) { ASSERT_SAME("%#x", 255); }
END_TEST

START_TEST(hex_hash_upper) { ASSERT_SAME("%#X", 255); }
END_TEST

START_TEST(hex_hash_zero_value) { ASSERT_SAME("%#x", 0); }
END_TEST

START_TEST(hex_zero_padded_width) { ASSERT_SAME("%08x", 255); }
END_TEST



START_TEST(float_default_precision) { ASSERT_SAME("%f", 3.14); }
END_TEST

START_TEST(float_negative) { ASSERT_SAME("%f", -3.14); }
END_TEST

START_TEST(float_zero) { ASSERT_SAME("%f", 0.0); }
END_TEST

START_TEST(float_custom_precision) { ASSERT_SAME("%.2f", 3.14159); }
END_TEST

START_TEST(float_zero_precision) { ASSERT_SAME("%.0f", 3.7); }
END_TEST

START_TEST(float_width_and_precision) { ASSERT_SAME("[%10.2f]", 3.14159); }
END_TEST

START_TEST(float_left_justify) { ASSERT_SAME("[%-10.2f]", 3.14159); }
END_TEST

START_TEST(float_zero_pad) { ASSERT_SAME("%010.2f", 3.14159); }
END_TEST

START_TEST(float_plus_flag) { ASSERT_SAME("%+.2f", 3.14159); }
END_TEST

START_TEST(float_large_value) { ASSERT_SAME("%f", 123456.789); }
END_TEST

START_TEST(float_long_double) { ASSERT_SAME("%Lf", 3.14159265358979L); }
END_TEST



START_TEST(exp_lower) { ASSERT_SAME("%e", 12345.6789); }
END_TEST

START_TEST(exp_upper) { ASSERT_SAME("%E", 12345.6789); }
END_TEST

START_TEST(exp_small_number) { ASSERT_SAME("%e", 0.0001234); }
END_TEST

START_TEST(exp_custom_precision) { ASSERT_SAME("%.2e", 12345.6789); }
END_TEST

START_TEST(exp_zero) { ASSERT_SAME("%e", 0.0); }
END_TEST



START_TEST(general_lower) { ASSERT_SAME("%g", 12345.6789); }
END_TEST

START_TEST(general_small) { ASSERT_SAME("%g", 0.0001234); }
END_TEST

START_TEST(general_big) { ASSERT_SAME("%g", 123456789.0); }
END_TEST

START_TEST(general_upper) { ASSERT_SAME("%G", 0.00001234); }
END_TEST

START_TEST(general_precision) { ASSERT_SAME("%.10g", 3.14159265358979); }
END_TEST

START_TEST(general_hash) { ASSERT_SAME("%#g", 100.0); }
END_TEST



START_TEST(pointer_null) { ASSERT_SAME("%p", (void *)0); }
END_TEST

START_TEST(pointer_value) {
  int x = 5;
  ASSERT_SAME("%p", (void *)&x);
}
END_TEST



START_TEST(percent_literal) { ASSERT_SAME("100%% done"); }
END_TEST



START_TEST(star_width) { ASSERT_SAME("[%*d]", 8, 42); }
END_TEST

START_TEST(star_precision) { ASSERT_SAME("%.*f", 3, 3.14159); }
END_TEST

START_TEST(star_width_and_precision) { ASSERT_SAME("%*.*f", 10, 3, 3.14159); }
END_TEST



START_TEST(combo_multiple_specs) {
  ASSERT_SAME("%s scored %d points (%.1f%%)", "Alice", 97, 97.4);
}
END_TEST

START_TEST(combo_plain_text_only) { ASSERT_SAME("just plain text, no specs"); }
END_TEST

Suite *s21_sprintf_suite(void) {
  Suite *suite = suite_create("s21_sprintf");

  TCase *tc = tcase_create("core");
  tcase_add_test(tc, char_plain);
  tcase_add_test(tc, char_width_right);
  tcase_add_test(tc, char_width_left);

  tcase_add_test(tc, string_plain);
  tcase_add_test(tc, string_empty);
  tcase_add_test(tc, string_width_right);
  tcase_add_test(tc, string_width_left);
  tcase_add_test(tc, string_precision);
  tcase_add_test(tc, string_width_and_precision);

  tcase_add_test(tc, int_zero);
  tcase_add_test(tc, int_positive);
  tcase_add_test(tc, int_negative);
  tcase_add_test(tc, int_width);
  tcase_add_test(tc, int_width_left);
  tcase_add_test(tc, int_zero_pad);
  tcase_add_test(tc, int_zero_pad_negative);
  tcase_add_test(tc, int_plus_flag);
  tcase_add_test(tc, int_space_flag);
  tcase_add_test(tc, int_precision);
  tcase_add_test(tc, int_precision_zero_value);
  tcase_add_test(tc, int_width_and_precision);
  tcase_add_test(tc, int_long_modifier);
  tcase_add_test(tc, int_short_modifier);
  tcase_add_test(tc, int_alias_i);

  tcase_add_test(tc, uint_plain);
  tcase_add_test(tc, uint_from_negative);
  tcase_add_test(tc, uint_width_zero_pad);

  tcase_add_test(tc, octal_plain);
  tcase_add_test(tc, octal_hash);
  tcase_add_test(tc, octal_hash_zero);

  tcase_add_test(tc, hex_lower);
  tcase_add_test(tc, hex_upper);
  tcase_add_test(tc, hex_hash);
  tcase_add_test(tc, hex_hash_upper);
  tcase_add_test(tc, hex_hash_zero_value);
  tcase_add_test(tc, hex_zero_padded_width);

  tcase_add_test(tc, float_default_precision);
  tcase_add_test(tc, float_negative);
  tcase_add_test(tc, float_zero);
  tcase_add_test(tc, float_custom_precision);
  tcase_add_test(tc, float_zero_precision);
  tcase_add_test(tc, float_width_and_precision);
  tcase_add_test(tc, float_left_justify);
  tcase_add_test(tc, float_zero_pad);
  tcase_add_test(tc, float_plus_flag);
  tcase_add_test(tc, float_large_value);
  tcase_add_test(tc, float_long_double);

  tcase_add_test(tc, exp_lower);
  tcase_add_test(tc, exp_upper);
  tcase_add_test(tc, exp_small_number);
  tcase_add_test(tc, exp_custom_precision);
  tcase_add_test(tc, exp_zero);

  tcase_add_test(tc, general_lower);
  tcase_add_test(tc, general_small);
  tcase_add_test(tc, general_big);
  tcase_add_test(tc, general_upper);
  tcase_add_test(tc, general_precision);
  tcase_add_test(tc, general_hash);

  tcase_add_test(tc, pointer_null);
  tcase_add_test(tc, pointer_value);

  tcase_add_test(tc, percent_literal);

  tcase_add_test(tc, star_width);
  tcase_add_test(tc, star_precision);
  tcase_add_test(tc, star_width_and_precision);

  tcase_add_test(tc, combo_multiple_specs);
  tcase_add_test(tc, combo_plain_text_only);

  suite_add_tcase(suite, tc);
  return suite;
}

int main(void) {
  Suite *suite = s21_sprintf_suite();
  SRunner *runner = srunner_create(suite);

  srunner_run_all(runner, CK_NORMAL);
  int failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return failed == 0 ? 0 : 1;
}

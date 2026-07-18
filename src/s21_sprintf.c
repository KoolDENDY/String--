#include "s21_sprintf_utils.h"

const char *s21_parse_spec(const char *format, va_list *args,
                            s21_spec_t *spec) {
  spec->minus = 0;
  spec->plus = 0;
  spec->space = 0;
  spec->hash = 0;
  spec->zero = 0;
  spec->width = 0;
  spec->precision = -1;
  spec->length = '\0';

  int reading_flags = 1;
  while (reading_flags) {
    if (*format == '-') {
      spec->minus = 1;
    } else if (*format == '+') {
      spec->plus = 1;
    } else if (*format == ' ') {
      spec->space = 1;
    } else if (*format == '#') {
      spec->hash = 1;
    } else if (*format == '0') {
      spec->zero = 1;
    } else {
      reading_flags = 0;
    }
    if (reading_flags) format++;
  }

  if (*format == '*') {
    int width = va_arg(*args, int);
    if (width < 0) {
      spec->minus = 1;
      width = -width;
    }
    spec->width = width;
    format++;
  } else {
    while (*format >= '0' && *format <= '9') {
      spec->width = spec->width * 10 + (*format - '0');
      format++;
    }
  }

  if (*format == '.') {
    format++;
    if (*format == '*') {
      int precision = va_arg(*args, int);
      spec->precision = precision < 0 ? -1 : precision;
      format++;
    } else {
      spec->precision = 0;
      while (*format >= '0' && *format <= '9') {
        spec->precision = spec->precision * 10 + (*format - '0');
        format++;
      }
    }
  }

  if (*format == 'h' || *format == 'l' || *format == 'L') {
    spec->length = *format;
    format++;
  }

  return format;
}

static int s21_dispatch(char *dst, char conv, va_list *args,
                         s21_spec_t spec) {
  int written = 0;
  if (conv == 'c') {
    written = s21_fmt_char(dst, args, spec);
  } else if (conv == 's') {
    written = s21_fmt_string(dst, args, spec);
  } else if (conv == 'd' || conv == 'i') {
    written = s21_fmt_signed(dst, args, spec);
  } else if (conv == 'u') {
    written = s21_fmt_unsigned(dst, args, spec, 10, 0);
  } else if (conv == 'o') {
    written = s21_fmt_unsigned(dst, args, spec, 8, 0);
  } else if (conv == 'x') {
    written = s21_fmt_unsigned(dst, args, spec, 16, 0);
  } else if (conv == 'X') {
    written = s21_fmt_unsigned(dst, args, spec, 16, 1);
  } else if (conv == 'f' || conv == 'e' || conv == 'E' || conv == 'g' ||
             conv == 'G') {
    written = s21_fmt_float(dst, args, spec, conv);
  } else if (conv == 'p') {
    written = s21_fmt_pointer(dst, args, spec);
  } else if (conv == '%') {
    written = s21_fmt_percent(dst);
  } else if (conv == '\0') {
    written = 0;
  } else {
    dst[0] = conv;
    written = 1;
  }
  return written;
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);

  int pos = 0;
  while (*format) {
    if (*format != '%') {
      str[pos++] = *format++;
      continue;
    }
    format++; 

    s21_spec_t spec;
    format = s21_parse_spec(format, &args, &spec);
    char conv = *format;
    if (conv) format++;

    pos += s21_dispatch(str + pos, conv, &args, spec);
  }
  str[pos] = '\0';

  va_end(args);
  return pos;
}

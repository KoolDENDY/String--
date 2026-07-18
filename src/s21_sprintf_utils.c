#include "s21_sprintf_utils.h"

#define S21_BUF 620

s21_size_t s21_len(const char *str) {
  s21_size_t len = 0;
  while (str[len]) len++;
  return len;
}

static int s21_pad_and_write(char *dst, char sign, const char *prefix,
                              const char *body, int body_len, s21_spec_t spec,
                              int zero_ok) {
  int sign_len = sign ? 1 : 0;
  int prefix_len = prefix ? (int)s21_len(prefix) : 0;
  int content_len = sign_len + prefix_len + body_len;
  int pad = spec.width > content_len ? spec.width - content_len : 0;
  int pos = 0;

  if (!spec.minus && !zero_ok) {
    for (int i = 0; i < pad; i++) dst[pos++] = ' ';
  }
  if (sign) dst[pos++] = sign;
  for (int i = 0; i < prefix_len; i++) dst[pos++] = prefix[i];
  if (!spec.minus && zero_ok) {
    for (int i = 0; i < pad; i++) dst[pos++] = '0';
  }
  for (int i = 0; i < body_len; i++) dst[pos++] = body[i];
  if (spec.minus) {
    for (int i = 0; i < pad; i++) dst[pos++] = ' ';
  }
  return pos;
}

int s21_fmt_char(char *dst, va_list *args, s21_spec_t spec) {
  char c = (char)va_arg(*args, int);
  return s21_pad_and_write(dst, 0, S21_NULL, &c, 1, spec, 0);
}

int s21_fmt_string(char *dst, va_list *args, s21_spec_t spec) {
  char *arg = va_arg(*args, char *);
  if (!arg) arg = "(null)";
  int len = (int)s21_len(arg);
  if (spec.precision >= 0 && spec.precision < len) len = spec.precision;
  return s21_pad_and_write(dst, 0, S21_NULL, arg, len, spec, 0);
}

int s21_fmt_percent(char *dst) {
  dst[0] = '%';
  return 1;
}

static int s21_uint_to_buf(unsigned long long value, int base, int upper,
                            char *buf) {
  const char *digset = upper ? "0123456789ABCDEF" : "0123456789abcdef";
  char tmp[70];
  int len = 0;
  if (value == 0) {
    tmp[len++] = '0';
  } else {
    while (value > 0) {
      tmp[len++] = digset[value % (unsigned)base];
      value /= (unsigned)base;
    }
  }
  for (int i = 0; i < len; i++) buf[i] = tmp[len - 1 - i];
  return len;
}

static int s21_apply_min_digits(char *buf, int len, int min_digits) {
  if (min_digits <= len) return len;
  int pad = min_digits - len;
  for (int i = len - 1; i >= 0; i--) buf[i + pad] = buf[i];
  for (int i = 0; i < pad; i++) buf[i] = '0';
  return min_digits;
}

int s21_fmt_signed(char *dst, va_list *args, s21_spec_t spec) {
  long long value;
  if (spec.length == 'l')
    value = va_arg(*args, long);
  else if (spec.length == 'h')
    value = (short)va_arg(*args, int);
  else
    value = va_arg(*args, int);

  int negative = value < 0;
  unsigned long long uvalue =
      negative ? (unsigned long long)(-(value + 1)) + 1ULL
               : (unsigned long long)value;

  char digits[S21_BUF];
  int len;
  if (uvalue == 0 && spec.precision == 0) {
    len = 0;
  } else {
    len = s21_uint_to_buf(uvalue, 10, 0, digits);
    if (spec.precision > len) len = s21_apply_min_digits(digits, len, spec.precision);
  }

  char sign = 0;
  if (negative)
    sign = '-';
  else if (spec.plus)
    sign = '+';
  else if (spec.space)
    sign = ' ';

  int zero_ok = spec.zero && spec.precision < 0;
  return s21_pad_and_write(dst, sign, S21_NULL, digits, len, spec, zero_ok);
}

int s21_fmt_unsigned(char *dst, va_list *args, s21_spec_t spec, int base,
                      int upper) {
  unsigned long long value;
  if (spec.length == 'l')
    value = va_arg(*args, unsigned long);
  else if (spec.length == 'h')
    value = (unsigned short)va_arg(*args, unsigned int);
  else
    value = va_arg(*args, unsigned int);

  char digits[S21_BUF];
  int len;
  int octal_hash = (base == 8 && spec.hash);
  if (value == 0 && spec.precision == 0 && !octal_hash) {
    len = 0;
  } else {
    len = s21_uint_to_buf(value, base, upper, digits);
    int min_digits = spec.precision > len ? spec.precision : len;
    if (octal_hash && (len == 0 || digits[0] != '0') && min_digits < len + 1) {
      min_digits = len + 1;
    }
    if (min_digits > len) len = s21_apply_min_digits(digits, len, min_digits);
  }

  const char *prefix = S21_NULL;
  if (base == 16 && spec.hash && value != 0) prefix = upper ? "0X" : "0x";

  int zero_ok = spec.zero && spec.precision < 0;
  return s21_pad_and_write(dst, 0, prefix, digits, len, spec, zero_ok);
}

int s21_fmt_pointer(char *dst, va_list *args, s21_spec_t spec) {
  void *ptr = va_arg(*args, void *);
  if (ptr == S21_NULL) {
    const char *nil = "(nil)";
    return s21_pad_and_write(dst, 0, S21_NULL, nil, (int)s21_len(nil), spec, 0);
  }
  unsigned long long value = (unsigned long long)(s21_size_t)ptr;
  char digits[S21_BUF];
  int len = s21_uint_to_buf(value, 16, 0, digits);
  return s21_pad_and_write(dst, 0, "0x", digits, len, spec, spec.zero);
}

static int s21_round_digits(long double frac, int n, char *out) {
  char tmp[S21_BUF];
  int cap = n + 1;
  if (cap > S21_BUF - 10) cap = S21_BUF - 10;
  long double v = frac;
  for (int i = 0; i < cap; i++) {
    v *= 10.0L;
    int d = (int)floorl(v);
    if (d > 9) d = 9;
    if (d < 0) d = 0;
    tmp[i] = (char)d;
    v -= d;
  }
  int carry = tmp[cap - 1] >= 5 ? 1 : 0;
  for (int i = cap - 2; i >= 0; i--) {
    int d = tmp[i] + carry;
    if (d == 10) {
      d = 0;
      carry = 1;
    } else {
      carry = 0;
    }
    tmp[i] = (char)d;
  }
  for (int i = 0; i < n && i < cap - 1; i++) out[i] = (char)('0' + tmp[i]);
  return carry;
}

static int s21_int_part_digits(long double value, char *out) {
  int len = 0;
  if (value < 1.0L) {
    out[0] = '0';
    len = 1;
  } else {
    char tmp[S21_BUF];
    int t = 0;
    while (value >= 1.0L && t < S21_BUF - 10) {
      long double digit = fmodl(value, 10.0L);
      tmp[t++] = (char)('0' + (int)(digit + 0.5L));
      value = floorl(value / 10.0L);
    }
    for (int i = 0; i < t; i++) out[len++] = tmp[t - 1 - i];
  }
  return len;
}

static int s21_increment_decimal(char *digits, int len) {
  int i = len - 1;
  while (i >= 0) {
    if (digits[i] == '9') {
      digits[i] = '0';
      i--;
    } else {
      digits[i]++;
      break;
    }
  }
  if (i < 0) {
    for (int j = len; j > 0; j--) digits[j] = digits[j - 1];
    digits[0] = '1';
    len++;
  }
  return len;
}

static int s21_build_fixed(long double mag, int precision, int hash,
                            char *out) {
  long double int_part = floorl(mag);
  long double frac_part = mag - int_part;

  char int_digits[S21_BUF];
  int int_len = s21_int_part_digits(int_part, int_digits);

  char frac_digits[S21_BUF];
  int carry = s21_round_digits(frac_part, precision, frac_digits);
  if (carry) int_len = s21_increment_decimal(int_digits, int_len);

  int pos = 0;
  for (int i = 0; i < int_len; i++) out[pos++] = int_digits[i];
  if (precision > 0 || hash) out[pos++] = '.';
  for (int i = 0; i < precision; i++) out[pos++] = frac_digits[i];
  return pos;
}

static int s21_build_exp(long double mag, int precision, int hash, int upper,
                          char *out) {
  int exp = 0;
  long double mantissa = 0.0L;
  if (mag != 0.0L) {
    exp = (int)floorl(log10l(mag));
    mantissa = mag / powl(10.0L, exp);
    if (mantissa >= 10.0L) {
      mantissa /= 10.0L;
      exp++;
    } else if (mantissa < 1.0L) {
      mantissa *= 10.0L;
      exp--;
    }
  }

  int lead = (int)floorl(mantissa);
  long double frac = mantissa - lead;
  char frac_digits[S21_BUF];
  int carry = s21_round_digits(frac, precision, frac_digits);
  if (carry) {
    lead++;
    if (lead == 10) {
      lead = 1;
      exp++;
    }
  }

  int pos = 0;
  out[pos++] = (char)('0' + lead);
  if (precision > 0 || hash) out[pos++] = '.';
  for (int i = 0; i < precision; i++) out[pos++] = frac_digits[i];
  out[pos++] = upper ? 'E' : 'e';
  out[pos++] = exp < 0 ? '-' : '+';

  int e = exp < 0 ? -exp : exp;
  char ebuf[16];
  int elen = s21_uint_to_buf((unsigned long long)e, 10, 0, ebuf);
  if (elen < 2) out[pos++] = '0';
  for (int i = 0; i < elen; i++) out[pos++] = ebuf[i];
  return pos;
}

static int s21_trim_fixed_zeros(char *out, int len) {
  int has_dot = 0;
  for (int i = 0; i < len; i++)
    if (out[i] == '.') has_dot = 1;
  if (!has_dot) return len;
  while (len > 0 && out[len - 1] == '0') len--;
  if (len > 0 && out[len - 1] == '.') len--;
  return len;
}

static int s21_trim_exp_zeros(char *out, int len) {
  int epos = -1;
  for (int i = 0; i < len && epos < 0; i++)
    if (out[i] == 'e' || out[i] == 'E') epos = i;
  if (epos < 0) return len;

  int has_dot = 0;
  for (int i = 0; i < epos; i++)
    if (out[i] == '.') has_dot = 1;
  if (!has_dot) return len;

  int mantissa_end = epos;
  while (mantissa_end > 0 && out[mantissa_end - 1] == '0') mantissa_end--;
  if (mantissa_end > 0 && out[mantissa_end - 1] == '.') mantissa_end--;

  int removed = epos - mantissa_end;
  for (int i = mantissa_end, j = epos; j < len; i++, j++) out[i] = out[j];
  return len - removed;
}

static int s21_build_general(long double mag, int precision, int hash,
                              int upper, char *out) {
  if (precision == 0) precision = 1;

  int exp = 0;
  if (mag != 0.0L) {
    exp = (int)floorl(log10l(mag));
    long double mantissa = mag / powl(10.0L, exp);
    if (mantissa >= 10.0L)
      exp++;
    else if (mantissa < 1.0L)
      exp--;
  }

  int pos;
  if (exp < -4 || exp >= precision) {
    pos = s21_build_exp(mag, precision - 1, hash, upper, out);
    if (!hash) pos = s21_trim_exp_zeros(out, pos);
  } else {
    int f_precision = precision - 1 - exp;
    if (f_precision < 0) f_precision = 0;
    pos = s21_build_fixed(mag, f_precision, hash, out);
    if (!hash) pos = s21_trim_fixed_zeros(out, pos);
  }
  return pos;
}

int s21_fmt_float(char *dst, va_list *args, s21_spec_t spec, char conv) {
  long double value = (spec.length == 'L') ? va_arg(*args, long double)
                                            : (long double)va_arg(*args, double);
  int negative = signbit((double)value) ? 1 : 0;
  long double mag = negative ? -value : value;

  char sign = 0;
  if (negative)
    sign = '-';
  else if (spec.plus)
    sign = '+';
  else if (spec.space)
    sign = ' ';

  char body[S21_BUF];
  int body_len;
  int is_upper = (conv == 'E' || conv == 'G');

  if (isnan((double)mag)) {
    const char *s = is_upper ? "NAN" : "nan";
    body_len = (int)s21_len(s);
    for (int i = 0; i < body_len; i++) body[i] = s[i];
    return s21_pad_and_write(dst, sign, S21_NULL, body, body_len, spec, 0);
  }
  if (isinf((double)mag)) {
    const char *s = is_upper ? "INF" : "inf";
    body_len = (int)s21_len(s);
    for (int i = 0; i < body_len; i++) body[i] = s[i];
    return s21_pad_and_write(dst, sign, S21_NULL, body, body_len, spec, 0);
  }

  int precision = spec.precision < 0 ? 6 : spec.precision;
  if (conv == 'f') {
    body_len = s21_build_fixed(mag, precision, spec.hash, body);
  } else if (conv == 'e' || conv == 'E') {
    body_len = s21_build_exp(mag, precision, spec.hash, conv == 'E', body);
  } else {
    body_len = s21_build_general(mag, precision, spec.hash, conv == 'G', body);
  }

  return s21_pad_and_write(dst, sign, S21_NULL, body, body_len, spec, spec.zero);
}

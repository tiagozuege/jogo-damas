#include <serial.h>
#include <stdint.h>
#include <stdio.h>

#define MAX_FILLER 11
#define FLOAT_PRECISION 9

static char *long_to_string_with_divisor(char *p,
                                         long num,
                                         unsigned radix,
                                         long divisor) {
  int i;
  char *q;
  long l, ll;

  l = num;
  if (divisor == 0) {
    ll = num;
  } else {
    ll = divisor;
  }

  q = p + MAX_FILLER;
  do {
    i = (int)(l % radix);
    i += '0';
    if (i > '9')
      i += 'A' - '0' - 10;
    *--q = i;
    l /= radix;
  } while ((ll /= radix) != 0);

  i = (int)(p + MAX_FILLER - q);
  do
    *p++ = *q++;
  while (--i);

  return p;
}

static char *ch_ltoa(char *p, long num, unsigned radix) {

  return long_to_string_with_divisor(p, num, radix, 0);
}

#if PRINTF_USE_FLOAT
static const long pow10[FLOAT_PRECISION] = {
    10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000
};

static char *ftoa(char *p, double num, unsigned long precision) {
  long l;

  if ((precision == 0) || (precision > FLOAT_PRECISION))
    precision = FLOAT_PRECISION;
  precision = pow10[precision - 1];

  l = (long)num;
  p = long_to_string_with_divisor(p, l, 10, 0);
  *p++ = '.';
  l = (long)((num - l) * precision);
  return long_to_string_with_divisor(p, l, 10, precision / 10);
}
#endif

int vprintf(const char *fmt, va_list ap) {
  char *p, *s, c, filler;
  int i, precision, width;
  int n = 0;
  uint8_t is_long, left_align;
  long l;
#if CHPRINTF_USE_FLOAT
  float f;
  char tmpbuf[2*MAX_FILLER + 1];
#else
  char tmpbuf[MAX_FILLER + 1];
#endif

  while (1) {
    c = *fmt++;
    if (c == 0)
      return n;
    if (c != '%') {
      serial_putc(c);
      n++;
      continue;
    }
    p = tmpbuf;
    s = tmpbuf;
    left_align = 0;
    if (*fmt == '-') {
      fmt++;
      left_align = 1;
    }
    filler = ' ';
    if (*fmt == '0') {
      fmt++;
      filler = '0';
    }
    width = 0;
    while (1) {
      c = *fmt++;
      if (c >= '0' && c <= '9')
        c -= '0';
      else if (c == '*')
        c = va_arg(ap, int);
      else
        break;
      width = width * 10 + c;
    }
    precision = 0;
    if (c == '.') {
      while (1) {
        c = *fmt++;
        if (c >= '0' && c <= '9')
          c -= '0';
        else if (c == '*')
          c = va_arg(ap, int);
        else
          break;
        precision *= 10;
        precision += c;
      }
    }
    /* Long modifier.*/
    if (c == 'l' || c == 'L') {
      is_long = 1;
      if (*fmt)
        c = *fmt++;
    }
    else
      is_long = (c >= 'A') && (c <= 'Z');

    /* Command decoding.*/
    switch (c) {
    case 'c':
      filler = ' ';
      *p++ = va_arg(ap, int);
      break;
    case 's':
      filler = ' ';
      if ((s = va_arg(ap, char *)) == 0)
        s = "(null)";
      if (precision == 0)
        precision = 32767;
      for (p = s; *p && (--precision >= 0); p++)
        ;
      break;
    case 'D':
    case 'd':
    case 'I':
    case 'i':
      if (is_long)
        l = va_arg(ap, long);
      else
        l = va_arg(ap, int);
      if (l < 0) {
        *p++ = '-';
        l = -l;
      }
      p = ch_ltoa(p, l, 10);
      break;
#if CHPRINTF_USE_FLOAT
    case 'f':
      f = (float) va_arg(ap, double);
      if (f < 0) {
        *p++ = '-';
        f = -f;
      }
      p = ftoa(p, f, precision);
      break;
#endif
    case 'X':
    case 'x':
      c = 16;
      goto unsigned_common;
    case 'U':
    case 'u':
      c = 10;
      goto unsigned_common;
    case 'O':
    case 'o':
      c = 8;
unsigned_common:
      if (is_long)
        l = va_arg(ap, unsigned long);
      else
        l = va_arg(ap, unsigned int);
      p = ch_ltoa(p, l, c);
      break;
    default:
      *p++ = c;
      break;
    }
    i = (int)(p - s);
    if ((width -= i) < 0)
      width = 0;
    if (left_align == 0)
      width = -width;
    if (width < 0) {
      if (*s == '-' && filler == '0') {
        serial_putc(*s++);
        n++;
        i--;
      }
      do {
        serial_putc(filler);
        n++;
      } while (++width != 0);
    }
    while (--i >= 0) {
      serial_putc(*s++);
      n++;
    }

    while (width) {
      serial_putc(filler);
      n++;
      width--;
    }
  }
}

int printf(const char *fmt, ...) {
  va_list ap;
  int formatted_bytes;

  va_start(ap, fmt);
  formatted_bytes = vprintf(fmt, ap);
  va_end(ap);

  return formatted_bytes;
}


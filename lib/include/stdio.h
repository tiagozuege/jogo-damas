#ifndef STDIO_H
#define STDIO_H

#include <stdarg.h>

#if !defined(PRINTF_USE_FLOAT)
#define PRINTF_USE_FLOAT	0
#endif

extern int printf(const char *fmt, ...);

#endif /* STDIO_H */


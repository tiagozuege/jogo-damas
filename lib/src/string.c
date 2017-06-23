#include <string.h>

void strcpy(const char *src, char *dst)
{
    while (*src)
        *dst++ = *src++;

    *dst = 0;
}


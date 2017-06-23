void *memset(void *dst, int c, int n)
{
    if (n) {
        char *d = dst;
        do {
            *d++ = c;
        } while (--n);
    }

    return dst;
}


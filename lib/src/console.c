#include <console.h>
#include <string.h>

static unsigned short * const vidptr = (unsigned short *) 0xb8000;

void putc(int x, int y, enum color fg, enum color bg, char c)
{
    vidptr[y * CONSOLE_COLS + x] = bg << 12 | fg << 8 | c;
}

void puts(int x, int y, enum color fg, enum color bg, const char *s)
{
    int px = x;

    for (; *s; s++, x++) {
        if (*s == '\n') {
            y++;
            x = px;
            continue;
        }

        putc(x, y, fg, bg, *s);
    }
}

void clear(enum color bg)
{
    int x, y;

    for (x = 0; x < CONSOLE_COLS; x++) {
        for (y = 0; y < CONSOLE_ROWS; y++)
            putc(x, y, bg, bg, ' ');
    }
}


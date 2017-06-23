#include <keyboard.h>
#include <io.h>

int getkey(void)
{
    unsigned char scan = 0;
    static unsigned char key = 0;

    scan = inb(0x60);

    if (scan != key) {
        key = scan;
        return key;
    }

    return -1;
}


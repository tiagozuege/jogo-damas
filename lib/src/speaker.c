#include <io.h>
#include <speaker.h>

void speaker_freq(unsigned int hz)
{
    unsigned int div = 1193180 / hz;

    outb(0x43, 0xb6);
    outb(0x42, (unsigned char) div);
    outb(0x42, (unsigned char) (div >> 8));
}

void speaker_on(void)
{
    outb(0x61, inb(0x61) | 0x03);
}

void speaker_off(void)
{
    outb(0x61, inb(0x61) & 0xfc);
}


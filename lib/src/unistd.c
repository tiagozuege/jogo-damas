#include <io.h>
#include <stdint.h>
#include <unistd.h>

/* Número de ticks da CPU por ms. */
static uint64_t tpms = 0;

void tickinit();

uint64_t rdtsc(void)
{
    uint32_t hi, lo;

    if (tpms == 0) {
        tpms = 1;
        tickinit();
    }

    asm("rdtsc" : "=a" (lo), "=d" (hi));

    return ((uint64_t) lo) | (((uint64_t) hi) << 32);
}

uint8_t rtcs(void)
{
    uint8_t last = 0, sec;

    do {
        do { outb(0x70, 0x0A); } while (inb(0x71) & 0x80);
        outb(0x70, 0x00);
        sec = inb(0x71);
    } while (sec != last && (last = sec));

    return sec;
}

void tps(void)
{
    static uint64_t ti = 0;
    static uint8_t last_sec = 0xFF;
    uint8_t sec = rtcs();

    if (sec != last_sec) {
        last_sec = sec;
        uint64_t tf = rdtsc();
        tpms = (uint32_t) ((tf - ti) >> 3) / 125;
        ti = tf;
    }
}

void tickinit(void)
{
    uint32_t itpms;

    /* Espera um segundo cheio para calibrar o temporizador. */
    tps();
    itpms = (uint32_t) tpms; while ((uint32_t) tpms == itpms) tps();
    itpms = (uint32_t) tpms; while ((uint32_t) tpms == itpms) tps();
}

uint64_t gtpms(void)
{
    if (tpms == 0) {
        tpms = 1;
        tickinit();
    }

    return tpms;
}

uint64_t sleep(uint64_t secs)
{
    int64_t t = rdtsc() + secs * 1e3 * tpms;

    while (t - (int64_t) rdtsc() > 0);

    return secs;
}

uint64_t msleep(uint64_t ms)
{
    int64_t t = rdtsc() + ms * tpms;

    while (t - (int64_t) rdtsc() > 0);

    return ms;
}


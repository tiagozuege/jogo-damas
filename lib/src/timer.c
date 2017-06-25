#include <stdint.h>
#include <timer.h>
#include <unistd.h>

void timer_init(timer_t *tmr, uint64_t t)
{
    tmr->tm = t * gtpms();
    tmr->to = rdtsc();
}

uint64_t timer_q(timer_t *tmr)
{
    return ((int64_t) rdtsc() - (int64_t) tmr->to) > (int64_t) tmr->tm;
}


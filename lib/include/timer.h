#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

typedef struct {
    uint64_t tm;
    uint64_t to;
} timer_t;

extern void timer_init(timer_t *tmr, uint64_t t);

extern uint64_t timer_q(timer_t *t);

#endif /* TIMER_H */


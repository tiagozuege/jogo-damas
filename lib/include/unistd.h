#ifndef UNISTD_H
#define UNISTD_H

extern uint64_t sleep(uint64_t secs);

extern uint64_t msleep(uint64_t ms);

extern uint64_t rdtsc(void);

extern uint64_t gtpms(void);

#endif /* UNISTD_H */


#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <stdlib.h>
#include <signal.h>

#include "watcher.h"

/* Worker responsible for checking for stagnations in program.
 * If workers don't respond in 2 seconds it performs gracefull shutdown
 * of the program. */
typedef struct Watchdog Watchdog;

struct Watchdog {
    Watcher* watcher;
    sig_atomic_t volatile* interrupt;
};

/* Starts Watchdog which checks every milisecond watcher for signal
 * from workers. If it doesn't get signal in 2 seconds it shuts down
 * the program. */
void watchdog_start(Watchdog* watchdog);

#endif

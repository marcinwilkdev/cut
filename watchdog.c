#include <stdio.h>

#include "watchdog.h"

#define STAGNATION_MILIS 2000
#define NANOS_IN_MILI 1000000

Watchdog watchdog_new(register Watcher* const watcher,
                      register sig_atomic_t volatile* const interrupt) {
    return (Watchdog){
        .watcher = watcher,
        .interrupt = interrupt,
        .milis = STAGNATION_MILIS,
    };
}

void watchdog_start(register Watchdog* const watchdog) {
    // can change to sleep with thread kill from other threads
    while (*watchdog->interrupt == 0) {
        nanosleep(&(struct timespec){.tv_nsec = NANOS_IN_MILI}, 0); // 1ms

        --watchdog->milis;

        if (watchdog->milis == 0) {
            fprintf(stderr,
                    "Workers not responding. Shutting down program...\n");
            *watchdog->interrupt = SIGTERM;

            break;
        }

        if (watcher_check(watchdog->watcher)) {
            watchdog->milis = STAGNATION_MILIS;
        }
    }
}

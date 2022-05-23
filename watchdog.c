#include <stdio.h>

#include "watchdog.h"

void watchdog_start(register Watchdog* const watchdog) {
    while (*watchdog->interrupt == 0) {
        if (!watcher_check(watchdog->watcher)) {
            fprintf(stderr,
                    "Workers not responding. Shutting down program...\n");

            // i think in stagnation program should quit gracefully
            // but code below could not be working on error
            *watchdog->interrupt = SIGTERM;
            break;

            // this is better if we should just forcefully shutdown
            /* exit(-1); */
        }
    }
}

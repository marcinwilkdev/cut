#include <stdio.h>

#include "../headers/watchdog.h"

void watchdog_start(register Watchdog* const watchdog) {
    while (*watchdog->interrupt == 0) {
        if (!watcher_check(watchdog->watcher)) {
            fprintf(stderr,
                    "Workers not responding. Shutting down program...\n");

            exit(-1);
        }
    }
}

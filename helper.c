#include <stdlib.h>

#include "helper.h"

FILE* open_stat_file(register sig_atomic_t volatile* const interrupt) {
    register FILE* const stat_file = fopen("/proc/stat", "r");

    if (stat_file == NULL) {
        fprintf(stderr,
                "Couldn't open /proc/stat file. Shutting down program...");

        *interrupt = SIGTERM;

        return NULL;
    }

    return stat_file;
}

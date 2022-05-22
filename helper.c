#include <stdlib.h>

#include "helper.h"

FILE* open_stat_file(void) {
    register FILE* const stat_file = fopen("/proc/stat", "r");

    if (stat_file == NULL) {
        perror("Couldn't open /proc/stat file.");
        exit(-1);
    }

    return stat_file;
}

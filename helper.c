#include <stdlib.h>
#include <string.h>

#include "helper.h"

#define BUFF_SIZE 256

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

size_t get_cores_count(register sig_atomic_t volatile* const interrupt) {
    register FILE* const stat = open_stat_file(interrupt);

    if (stat == NULL)
        return 0;

    size_t cores_count = 0;

    char buff[BUFF_SIZE];

    while(fgets(buff, BUFF_SIZE, stat) != NULL)
        if(strstr(buff, "cpu") != NULL)
            ++cores_count;

    fclose(stat);

    --cores_count;

    return cores_count;
}

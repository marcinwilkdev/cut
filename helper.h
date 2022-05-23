#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <signal.h>

/* Returns opened /proc/stat file or sets interrupt signal
 * and returns NULL if couldn't open. */
FILE* open_stat_file(sig_atomic_t volatile* interrupt);

#endif

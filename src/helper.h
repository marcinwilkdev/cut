#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <signal.h>

/* Returns opened /proc/stat file or sets interrupt signal
 * and returns NULL if couldn't open. */
FILE* open_stat_file(sig_atomic_t volatile* interrupt);

/* Returns numbers of cores found in /proc/stat file or
 * 0 if error with file encountered. */
size_t get_cores_count(sig_atomic_t volatile* interrupt);

#endif

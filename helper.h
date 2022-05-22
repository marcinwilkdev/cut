#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>

/* Returns opened /proc/stat file or ends program with error
 * if couldn't open. */
FILE* open_stat_file(void); // proably should also set signal var?

#endif

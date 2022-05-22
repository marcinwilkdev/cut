#ifndef WATCHER_H
#define WATCHER_H

#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

/* Watcher is used to detect stagnation in program. Each working
 * thread should use watcher_notify to signal that the program is running
 * and watchdog thread should use watcher_check to check if the program
 * is running. This struct has to be initialized with watcher_new function
 * and deleted with watcher_delete function. */
typedef struct Watcher Watcher;

struct Watcher {
    pthread_mutex_t mtx;
    bool flag;
    char padd[7];
};

/* Returns initialized Watcher instance. This instance has to be
 * deleted after usage with watcher_delete function. */
Watcher watcher_new(void);
/* Safely deletes Watcher instance. If NULL passed nothing happens. */
void watcher_delete(Watcher* watcher);

/* Sets watcher state to notified. This function can be safely used
 * between threads. If NULL passed nothing happens. */
void watcher_notify(Watcher* watcher);
/* Gets watcher state and sets it to unnotified. This function can be safely used
 * between threads. Returns false if watcher is NULL. */
bool watcher_check(Watcher* watcher);

#endif

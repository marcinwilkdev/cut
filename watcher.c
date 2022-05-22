#include "watcher.h"

Watcher watcher_new(void) {
    Watcher watcher = {
        .flag = false,
    };

    pthread_mutex_init(&watcher.mtx, NULL);

    return watcher;
}

void watcher_delete(register Watcher* const watcher) {
    if (watcher == NULL)
        return;

    pthread_mutex_destroy(&watcher->mtx);
}

void watcher_notify(register Watcher* const watcher) {
    if (watcher == NULL)
        return;

    pthread_mutex_lock(&watcher->mtx);

    watcher->flag = true;

    pthread_mutex_unlock(&watcher->mtx);
}

bool watcher_check(register Watcher* const watcher) {
    if (watcher == NULL)
        return false;

    pthread_mutex_lock(&watcher->mtx);

    register bool const flag = watcher->flag;

    watcher->flag = false;

    pthread_mutex_unlock(&watcher->mtx);

    return flag;
}

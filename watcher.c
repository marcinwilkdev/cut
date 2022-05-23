#include "watcher.h"

#define TWO_SECONDS 2

Watcher watcher_new(void) {
    Watcher watcher = {.flag = false};

    pthread_mutex_init(&watcher.mtx, NULL);
    pthread_cond_init(&watcher.cond, NULL);

    return watcher;
}

void watcher_delete(register Watcher* const watcher) {
    if (watcher == NULL)
        return;

    pthread_mutex_destroy(&watcher->mtx);
    pthread_cond_destroy(&watcher->cond);
}

void watcher_notify(register Watcher* const watcher) {
    if (watcher == NULL)
        return;

    pthread_mutex_lock(&watcher->mtx);

    watcher->flag = true;

    pthread_cond_signal(&watcher->cond);

    pthread_mutex_unlock(&watcher->mtx);
}

bool watcher_check(register Watcher* const watcher) {
    if (watcher == NULL)
        return false;

    pthread_mutex_lock(&watcher->mtx);

    struct timespec two_seconds_later = {0};
    clock_gettime(CLOCK_REALTIME, &two_seconds_later);

    two_seconds_later.tv_sec += TWO_SECONDS;

    int wait_result = 0;

    while (!watcher->flag) {
        wait_result = pthread_cond_timedwait(&watcher->cond, &watcher->mtx,
                                             &two_seconds_later);

        if (wait_result > 0)
            break;
    }

    watcher->flag = false;

    pthread_mutex_unlock(&watcher->mtx);

    return wait_result == 0;
}

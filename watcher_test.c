#include <assert.h>

#include "watcher_test.h"

#include "watcher.h"

void watcher_creation_test(void) {
    Watcher watcher = watcher_new();

    assert(watcher.flag == false);

    watcher_delete(&watcher);
    watcher_delete(NULL);
}

void watcher_notifying_test(void) {
    Watcher watcher = watcher_new();

    assert(watcher.flag == false);

    watcher_notify(&watcher);

    assert(watcher_check(&watcher) == true);
    assert(watcher_check(&watcher) == false);

    watcher_delete(&watcher);

    watcher_notify(NULL);
    assert(watcher_check(NULL) == false);
}

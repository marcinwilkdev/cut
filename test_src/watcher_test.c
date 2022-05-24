#include <assert.h>

#include "../src/watcher.h"

static void watcher_creation_test(void) {
    Watcher watcher = watcher_new();

    assert(watcher.flag == false);

    watcher_delete(&watcher);
    watcher_delete(NULL);
}

static void watcher_notifying_test(void) {
    Watcher watcher = watcher_new();

    assert(watcher.flag == false);

    watcher_notify(&watcher);

    assert(watcher_check(&watcher) == true);
    assert(watcher_check(&watcher) == false);

    watcher_delete(&watcher);

    watcher_notify(NULL);
    assert(watcher_check(NULL) == false);
}

int main(void) {
    watcher_creation_test();
    watcher_notifying_test();

    return EXIT_SUCCESS;
}

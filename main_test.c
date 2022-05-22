#include <stdlib.h>
#include <stdio.h>

#include "channel_test.h"
#include "watcher_test.h"
#include "text_message_test.h"

int main(void) {
    channel_creation_test();
    channel_push_pop_test();
    channel_push_pop_multithread_test();

    watcher_creation_test();
    watcher_notifying_test();

    text_message_creation_test();
    text_message_empty_test();

    puts("All tests passed succesfully.");

    return EXIT_SUCCESS;
}

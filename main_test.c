#include <stdlib.h>
#include <stdio.h>

#include "channel_test.h"
#include "watcher_test.h"
#include "text_message_test.h"
#include "log_message_test.h"
#include "helper_test.h"
#include "reader_test.h"
#include "core_util_message_test.h"
#include "analyzer_test.h"
#include "printer_test.h"

int main(void) {
    channel_creation_test();
    channel_push_pop_test();
    channel_push_pop_multithread_test();

    watcher_creation_test();
    watcher_notifying_test();

    text_message_creation_test();
    text_message_empty_test();

    log_message_creation_test();
    log_message_empty_test();

    open_stat_file_works();

    reader_working_test();

    core_util_message_creation_test();
    core_util_message_empty_test();

    get_cores_count_works();

    analyzer_working_test();

    printer_working_test();

    puts("All tests passed succesfully.");

    return EXIT_SUCCESS;
}

#include <stdlib.h>
#include <stdio.h>

#include "../test_headers/channel_test.h"
#include "../test_headers/watcher_test.h"
#include "../test_headers/text_message_test.h"
#include "../test_headers/log_message_test.h"
#include "../test_headers/helper_test.h"
#include "../test_headers/reader_test.h"
#include "../test_headers/core_util_message_test.h"
#include "../test_headers/analyzer_test.h"
#include "../test_headers/printer_test.h"
#include "../test_headers/logger_test.h"

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

    logger_working_test();

    puts("All tests passed succesfully.");

    return EXIT_SUCCESS;
}

#include <stdlib.h>

#include "analyzer.h"
#include "core_util_message.h"
#include "helper.h"
#include "log_message.h"
#include "printer.h"
#include "printer_test.h"
#include "reader.h"
#include "text_message.h"
#include "logger.h"
#include "watchdog.h"

#define CHANNEL_SIZE 1000

static sig_atomic_t volatile interrupt = 0;

inline static void* reader_thread_start(void* const r) {
    register Reader* const reader = r;

    reader_start(reader);

    return NULL;
}

inline static void* analyzer_thread_start(void* const a) {
    register Analyzer* const analyzer = a;

    analyzer_start(analyzer);

    return NULL;
}

inline static void* printer_thread_start(void* const p) {
    register Printer* const printer = p;

    printer_start(printer);

    return NULL;
}

inline static void* logger_thread_start(void* const l) {
    register Logger* const logger = l;

    logger_start(logger);

    return NULL;
}

inline static void* watchdog_thread_start(void* const w) {
    register Watchdog* const watchdog = w;

    watchdog_start(watchdog);

    return NULL;
}

static void signal_handler(int const sig) {
    interrupt = sig;
}

int main(void) {
    signal(SIGTERM, signal_handler);

    register Channel* const text_channel =
        channel_new(CHANNEL_SIZE, sizeof(Text_message*));
    register Channel* const log_channel =
        channel_new(CHANNEL_SIZE, sizeof(Log_message*));
    register Channel* const core_util_channel =
        channel_new(CHANNEL_SIZE, sizeof(Core_util_message*));

    Watcher watcher = watcher_new();

    register size_t const cores_count = get_cores_count(&interrupt);

    Reader reader = {
        .text_channel = text_channel,
        .log_channel = log_channel,
        .interrupt = &interrupt,
        .watcher = &watcher,
    };

    register Analyzer* const analyzer = analyzer_new(
        text_channel, core_util_channel, log_channel, &watcher, cores_count);

    Printer printer = {
        .core_util_channel = core_util_channel,
        .log_channel = log_channel,
        .watcher = &watcher,
    };

    Logger logger = {
        .log_channel = log_channel,
    };

    Watchdog watchdog = watchdog_new(&watcher, &interrupt);

    pthread_t threads[5];

    pthread_create(&threads[0], NULL, reader_thread_start, &reader);
    pthread_create(&threads[1], NULL, analyzer_thread_start, analyzer);
    pthread_create(&threads[2], NULL, printer_thread_start, &printer);
    pthread_create(&threads[3], NULL, logger_thread_start, &logger);
    pthread_create(&threads[4], NULL, watchdog_thread_start, &watchdog);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);
    pthread_join(threads[3], NULL);
    pthread_join(threads[4], NULL);

    analyzer_delete(analyzer);

    channel_delete(text_channel);
    channel_delete(log_channel);
    channel_delete(core_util_channel);

    watcher_delete(&watcher);

    return EXIT_SUCCESS;
}

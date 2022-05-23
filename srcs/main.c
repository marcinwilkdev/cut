#include <stdlib.h>
#include <string.h>

#include "../headers/analyzer.h"
#include "../headers/core_util_message.h"
#include "../headers/helper.h"
#include "../headers/log_message.h"
#include "../headers/logger.h"
#include "../headers/printer.h"
#include "../headers/reader.h"
#include "../headers/text_message.h"
#include "../headers/watchdog.h"

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

static void signal_handler(register int const sig) {
    if (sig == SIGTERM) {
        interrupt = sig;
    }
}

int main(void) {
    signal(SIGTERM, signal_handler);

    register Channel* const text_channel =
        channel_new(CHANNEL_SIZE, sizeof(Text_message*));
    register Channel* const log_channel =
        channel_new(CHANNEL_SIZE, sizeof(Log_message*));
    register Channel* const core_util_channel =
        channel_new(CHANNEL_SIZE, sizeof(Core_util_message*));

    if (text_channel == NULL || log_channel == NULL ||
        core_util_channel == NULL) {
        channel_delete(text_channel);
        channel_delete(log_channel);
        channel_delete(core_util_channel);

        fprintf(stderr, "Can't allocate memory, shutting down program...");
        exit(-1);
    }

    Watcher watcher = watcher_new();

    register size_t const cores_count = get_cores_count(&interrupt);

    if (cores_count == 0) {
        channel_delete(text_channel);
        channel_delete(log_channel);
        channel_delete(core_util_channel);

        fprintf(
            stderr,
            "Can't read cores count from /proc/stat. Shutting down program...");
        exit(-1);
    }

    Reader reader = {
        .text_channel = text_channel,
        .log_channel = log_channel,
        .interrupt = &interrupt,
        .watcher = &watcher,
    };

    register Analyzer* const analyzer = analyzer_new(
        text_channel, core_util_channel, log_channel, &watcher, cores_count);

    if (analyzer == NULL) {
        channel_delete(text_channel);
        channel_delete(log_channel);
        channel_delete(core_util_channel);

        fprintf(stderr, "Can't allocate memory, shutting down program...");
        exit(-1);
    }

    Printer printer = {
        .core_util_channel = core_util_channel,
        .log_channel = log_channel,
        .watcher = &watcher,
    };

    Logger logger = {
        .log_channel = log_channel,
    };

    Watchdog watchdog = {
        .watcher = &watcher,
        .interrupt = &interrupt,
    };

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

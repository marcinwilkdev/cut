#include <assert.h>

#include "analyzer_test.h"

#include "analyzer.h"
#include "core_util_message.h"
#include "helper.h"
#include "log_message.h"
#include "reader.h"
#include "text_message.h"

#define BIG_CHANNEL_SIZE 100

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

void analyzer_working_test(void) {
    Channel* const text_channel =
        channel_new(BIG_CHANNEL_SIZE, sizeof(Text_message*));
    Channel* const log_channel =
        channel_new(BIG_CHANNEL_SIZE, sizeof(Log_message*));
    Channel* const core_util_channel =
        channel_new(BIG_CHANNEL_SIZE, sizeof(Core_util_message*));

    register size_t const cores_count = get_cores_count(NULL);

    register Analyzer* const analyzer = analyzer_new(
        text_channel, core_util_channel, log_channel, NULL, cores_count);

    Reader reader = {
        .text_channel = text_channel,
        .log_channel = log_channel,
        .interrupt = &interrupt,
    };

    pthread_t threads[2];

    pthread_create(&threads[0], NULL, reader_thread_start, &reader);
    pthread_create(&threads[1], NULL, analyzer_thread_start, analyzer);

    nanosleep(&(struct timespec){.tv_nsec = 1000000}, NULL);

    interrupt = SIGTERM;

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    analyzer_delete(analyzer);

    for (;;) {
        Core_util_message* core_util_message = NULL;

        channel_pop(core_util_channel, &core_util_message);

        if (core_util_message->empty) {
            core_util_message_delete(core_util_message);

            break;
        }

        assert(core_util_message->core_num < cores_count);

        core_util_message_delete(core_util_message);
    }

    for (;;) {
        Log_message* log_message = NULL;

        channel_pop(log_channel, &log_message);

        if (log_message_is_empty(log_message)) {
            log_message_delete(log_message);

            break;
        }

        log_message_delete(log_message);
    }

    channel_delete(text_channel);
    channel_delete(log_channel);
    channel_delete(core_util_channel);
}

#include <pthread.h>
#include <signal.h>
#include <stdio.h>

#include "reader_test.h"

#include "reader.h"
#include "text_message.h"
#include "log_message.h"

#define BIG_CHANNEL_SIZE 100

static sig_atomic_t volatile interrupt = 0;

inline static void* reader_thread_start(void* const r) {
    Reader* const reader = r;

    reader_start(reader);

    return NULL;
}

void reader_working_test(void) {
    Channel* const text_channel = channel_new(BIG_CHANNEL_SIZE, sizeof(Text_message*));
    Channel* const log_channel = channel_new(BIG_CHANNEL_SIZE, sizeof(Log_message*));

    Reader reader = {
        .text_channel = text_channel,
        .log_channel = log_channel,
        .interrupt = &interrupt,
    };

    pthread_t reader_thread = {0};

    pthread_create(&reader_thread, NULL, reader_thread_start, &reader);

    nanosleep(&(struct timespec){.tv_nsec = 1000000}, NULL);

    interrupt = SIGTERM;

    pthread_join(reader_thread, NULL);

    for (;;) {
        Text_message* text_message = NULL;
        Log_message* log_message = NULL;

        channel_pop(text_channel, &text_message);
        channel_pop(log_channel, &log_message);

        if (text_message_is_empty(text_message)) {
            text_message_delete(text_message);
            log_message_delete(log_message);

            break;
        }

        text_message_delete(text_message);
        log_message_delete(log_message);
    }

    channel_delete(text_channel);
    channel_delete(log_channel);
}
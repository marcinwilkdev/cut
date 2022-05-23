#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "helper.h"
#include "log_message.h"
#include "reader.h"
#include "text_message.h"

#define BUFF_SIZE 256
#define ONE_SECOND 1

inline static void reader_send_log(register Reader* const restrict reader,
                                   char const text[const restrict]) {
    char buff[BUFF_SIZE];

    register int const log_len = sprintf(buff, "%s", text);

    if (log_len < 0) {
        fprintf(stderr, "Couldn't create log message.");
    } else {
        Log_message* const log_message =
            log_message_new(log_reader, (size_t)log_len + 1, buff);

        if (log_message == NULL)
            fprintf(stderr, "Couldn't create log message.");
        else
            channel_push(reader->log_channel, &log_message);
    }
}

inline static void reader_send_message(register Reader* const reader,
                                       char const buff[const]) {
    register size_t const line_len = strlen(buff);

    Text_message* const text_message = text_message_new(line_len + 1, buff);

    if (text_message == NULL)
        reader_send_log(reader, "Couldn't send message through text channel.");
    else
        channel_push(reader->text_channel, &text_message);
}

inline static void reader_send_stat_file(register Reader* const reader) {
    register FILE* const stat = open_stat_file(reader->interrupt);

    if (stat == NULL)
        return;

    char buff[BUFF_SIZE];

    while (fgets(buff, BUFF_SIZE, stat) != NULL) {
        reader_send_message(reader, buff);
        reader_send_log(reader, "Sending read line to analyzer...");
        watcher_notify(reader->watcher);
    }

    fclose(stat);
}

void reader_start(register Reader* const reader) {
    while (*reader->interrupt == 0) {
        reader_send_stat_file(reader);
        sleep(ONE_SECOND);
    }

    Text_message* const message = text_message_empty();
    channel_push(reader->text_channel, &message);

    Log_message* const log = log_message_empty();
    channel_push(reader->log_channel, &log);
}

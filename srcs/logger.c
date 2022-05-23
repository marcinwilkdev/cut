#include <stdio.h>

#include "../headers/logger.h"
#include "../headers/log_message.h"

#define LOG_FILE_PATH "log_file"

inline static void logger_save_log(register Log_message* const log_message, register FILE* const log_file) {
    register char const* const header = (char const*[]){
        [log_reader] = "[reader]",
        [log_analyzer] = "[analyzer]",
        [log_printer] = "[printer]",
    }[log_message_type(log_message)];

    fprintf(log_file, "%s: %s\n", header, log_message_text(log_message));
    fflush(log_file);
}

void logger_start(register Logger* const logger) {
    register FILE* const log_file = fopen(LOG_FILE_PATH, "w");

    for (;;) {
        Log_message* log_message = {0};
        channel_pop(logger->log_channel, &log_message);

        if (log_message_is_empty(log_message)) {
            log_message_delete(log_message);
            break;
        }

        logger_save_log(log_message, log_file);

        log_message_delete(log_message);
    }

    fclose(log_file);
}

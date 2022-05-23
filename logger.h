#ifndef LOGGER_H
#define LOGGER_H

#include "channel.h"

/* Worker responsible for taking log messages from all workers,
 * and saving them to the log file. */
typedef struct Logger Logger;

struct Logger {
    Channel* log_channel;
};

/* Starts Logger which will read log_messages from log_message_channel until
 * empty message encountered. Every message is saved in the log file so
 * that logs can be easily analyzed. Returns if analyzer is NULL. */
void logger_start(Logger* logger);

#endif

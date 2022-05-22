#include <string.h>

#include "log_message.h"

struct Log_message {
    enum log_type type;
    char text[];
};

Log_message* log_message_new(enum log_type const type,
                             register size_t const len,
                             char const text[const len]) {
    if (len == 0)
        return NULL;

    register size_t const log_message_size =
        sizeof(enum log_type) + sizeof(char[len]);

    register Log_message* const log_message = malloc(log_message_size);

    if (log_message == NULL)
        return NULL;

    *log_message = (Log_message){
        .type = type,
    };

    memcpy(log_message->text, text, sizeof(char[len]));

    return log_message;
}

Log_message* log_message_empty(void) {
    register size_t const log_message_size = sizeof(enum log_type);

    register Log_message* const log_message = malloc(log_message_size);

    if (log_message == NULL)
        return NULL;

    *log_message = (Log_message){
        .type = log_empty,
    };

    return log_message;
}

enum log_type log_message_type(register Log_message const* const log_message) {
    if (log_message == NULL)
        return log_empty;

    return log_message->type;
}

char const* log_message_text(register Log_message const* const log_message) {
    if (log_message_is_empty(log_message))
        return NULL;

    return log_message->text;
}

bool log_message_is_empty(register Log_message const* const log_message) {
    if (log_message == NULL)
        return true;

    return log_message->type == log_empty;
}

void log_message_delete(register Log_message* const log_message) {
    free(log_message);
}

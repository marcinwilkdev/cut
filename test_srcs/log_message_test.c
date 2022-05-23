#include <string.h>
#include <assert.h>

#include "../test_headers/log_message_test.h"

#include "../headers/log_message.h"

void log_message_creation_test(void) {
    register Log_message* const log_message = log_message_new(log_reader, strlen("Test") + 1, "Test");

    assert(log_message != NULL);
    assert(!log_message_is_empty(log_message));
    assert(strcmp("Test", log_message_text(log_message)) == 0);

    log_message_delete(log_message);
    log_message_delete(NULL);

    assert(log_message_new(log_empty, 0, NULL) == NULL);
}

void log_message_empty_test(void) {
    register Log_message* const log_message = log_message_empty();

    assert(log_message != NULL);
    assert(log_message_is_empty(log_message));
    assert(log_message_text(log_message) == NULL);

    log_message_delete(log_message);

    assert(log_message_type(NULL) == log_empty);
    assert(log_message_text(NULL) == NULL);
    assert(log_message_is_empty(NULL) == true);
}

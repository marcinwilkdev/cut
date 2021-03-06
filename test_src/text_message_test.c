#include <string.h>
#include <assert.h>

#include "../src/text_message.h"

static void text_message_creation_test(void) {
    register Text_message* const message = text_message_new(strlen("Test") + 1, "Test");

    assert(message != NULL);
    assert(!text_message_is_empty(message));
    assert(strcmp("Test", text_message_message(message)) == 0);

    text_message_delete(message);
    text_message_delete(NULL);

    assert(text_message_new(0, NULL) == NULL);
}

static void text_message_empty_test(void) {
    register Text_message* const message = text_message_empty();

    assert(message != NULL);
    assert(text_message_is_empty(message));
    assert(text_message_message(message) == NULL);

    text_message_delete(message);

    assert(text_message_is_empty(NULL));
    assert(text_message_message(NULL) == NULL);
}

int main(void) {
    text_message_creation_test();
    text_message_empty_test();

    return EXIT_SUCCESS;
}

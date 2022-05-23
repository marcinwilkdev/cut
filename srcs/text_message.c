#include <string.h>

#include "../headers/text_message.h"

struct Text_message {
    bool empty;
    char text[];
};

Text_message* text_message_empty(void) {
    register size_t const message_size = sizeof(Text_message);

    register Text_message* const message = malloc(message_size);

    if (message == NULL)
        return NULL;

    *message = (Text_message){
        .empty = true,
    };

    return message;
}

bool text_message_is_empty(register Text_message const* const message) {
    if (message == NULL)
        return true;

    return message->empty;
}

char const* text_message_message(register Text_message const* message) {
    if (text_message_is_empty(message))
        return NULL;

    return message->text;
}

Text_message* text_message_new(register size_t const len,
                               char const message_text[const len]) {
    if (len == 0)
        return NULL;

    register size_t const message_size =
        sizeof(Text_message) + sizeof(char[len]);

    register Text_message* const message = malloc(message_size);

    if (message == NULL)
        return NULL;

    *message = (Text_message){
        .empty = false,
    };

    memcpy(message->text, message_text, sizeof(char[len]));

    return message;
}

void text_message_delete(register Text_message* const message) {
    free(message);
}

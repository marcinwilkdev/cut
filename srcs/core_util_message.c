#include "../headers/core_util_message.h"

Core_util_message* core_util_message_new(register size_t const core_num,
                                         register size_t const util) {
    Core_util_message* core_util_message = malloc(sizeof(Core_util_message));

    if (core_util_message == NULL)
        return NULL;

    *core_util_message = (Core_util_message){
        .core_num = core_num,
        .util = util,
        .empty = false,
    };

    return core_util_message;
}

void core_util_message_delete(
    register Core_util_message* const core_util_message) {
    free(core_util_message);
}

Core_util_message* core_util_message_empty(void) {
    register Core_util_message* const core_util_message =
        malloc(sizeof(Core_util_message));

    if (core_util_message == NULL)
        return NULL;

    *core_util_message = (Core_util_message){
        .empty = true,
    };

    return core_util_message;
}

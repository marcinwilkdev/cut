#include <assert.h>

#include "../src/core_util_message.h"

static void core_util_message_creation_test(void) {
    register Core_util_message* const core_util_message = core_util_message_new(0, 0);

    assert(core_util_message != NULL);
    assert(!core_util_message->empty);
    assert(core_util_message->core_num == 0);
    assert(core_util_message->util == 0);

    core_util_message_delete(core_util_message);
    core_util_message_delete(NULL);
}

static void core_util_message_empty_test(void) {
    register Core_util_message* const core_util_message = core_util_message_empty();

    assert(core_util_message != NULL);
    assert(core_util_message->empty);

    core_util_message_delete(core_util_message);
}

int main(void) {
    core_util_message_creation_test();
    core_util_message_empty_test();

    return EXIT_SUCCESS;
}

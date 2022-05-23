#include <assert.h>

#include "core_util_message_test.h"

#include "core_util_message.h"

void core_util_message_creation_test(void) {
    register Core_util_message* const core_util_message = core_util_message_new(0, 0);

    assert(core_util_message != NULL);
    assert(!core_util_message->empty);
    assert(core_util_message->core_num == 0);
    assert(core_util_message->util == 0);

    core_util_message_delete(core_util_message);
    core_util_message_delete(NULL);
}

void core_util_message_empty_test(void) {
    register Core_util_message* const core_util_message = core_util_message_empty();

    assert(core_util_message != NULL);
    assert(core_util_message->empty);

    core_util_message_delete(core_util_message);
}

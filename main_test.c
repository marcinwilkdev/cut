#include <stdlib.h>
#include <stdio.h>

#include "channel_test.h"

int main(void) {
    channel_creation_test();
    channel_push_pop_test();
    channel_push_pop_multithread_test();

    puts("All tests passed succesfully.");

    return EXIT_SUCCESS;
}

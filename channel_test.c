#include <assert.h>
#include <pthread.h>

#include "channel_test.h"

void channel_creation_test(void) {
    Channel* c = channel_new(1, 1);

    assert(c != NULL);

    channel_delete(c);

    channel_delete(NULL);

    assert(channel_new(0, 1) == NULL);
    assert(channel_new(1, 0) == NULL);
    assert(channel_new(0, 0) == NULL);
}

void channel_push_pop_test(void) {
    Channel* c = channel_new(5, sizeof(int));

    for (int i = 0; i < 5; ++i)
        assert(channel_push(c, &i) == 0);

    for (int i = 0; i < 5; ++i) {
        int value = 0;

        assert(channel_pop(c, &value) == 0);

        assert(value == i);
    }

    assert(channel_push(c, NULL) == -1);

    channel_delete(c);

    assert(channel_push(NULL, &(int){5}) == -1);
    assert(channel_push(NULL, NULL) == -1);
}

static void* push_thread(void* const c) {
    register Channel* const channel = c;

    for (int i = 0; i < 100; ++i)
        assert(channel_push(channel, &i) == 0);

    return NULL;
}

static void* pop_thread(void* const c) {
    register Channel* const channel = c;

    for (int i = 0; i < 100; ++i) {
        int value = 0;

        assert(channel_pop(channel, &value) == 0);

        assert(value == i);
    }

    return NULL;
}

void channel_push_pop_multithread_test(void) {
    register Channel* const channel = channel_new(5, sizeof(int));

    pthread_t threads[2];

    pthread_create(&threads[0], NULL, push_thread, channel);
    pthread_create(&threads[1], NULL, pop_thread, channel);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    channel_delete(channel);
}

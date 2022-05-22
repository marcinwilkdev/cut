#include <pthread.h>
#include <stdint.h>
#include <string.h>

#include "channel.h"

struct Channel {
    pthread_mutex_t mtx;   // guards channel's memory
    pthread_cond_t add;    // used to signal thread waiting to push to channel
    pthread_cond_t remove; // used to signal thread waiting to pop of channel

    size_t n_elem;    // channel's capacity
    size_t size;      // current elements count
    size_t elem_size; // element's size in bytes
    size_t start;     // index into buf where elements start
    uint8_t buf[];    // memory holding elements
};

static size_t channel_index(Channel const* const c, size_t pos) {
    pos %= c->n_elem;

    size_t index = c->start + pos;
    index %= c->n_elem;

    return index;
}

int channel_push(register Channel* const restrict c,
                 register void const* const restrict elem) {
    if (c == NULL || elem == NULL)
        return -1;

    pthread_mutex_lock(&c->mtx);

    while (c->size == c->n_elem)
        pthread_cond_wait(&c->add, &c->mtx);

    register size_t const elem_index = channel_index(c, c->size);
    register uint8_t* const elem_ptr = &c->buf[elem_index * c->elem_size];

    memcpy(elem_ptr, elem, c->elem_size);

    ++c->size;

    pthread_cond_signal(&c->remove);
    pthread_mutex_unlock(&c->mtx);

    return 0;
}

int channel_pop(register Channel* const restrict c,
                register void* const restrict elem) {
    if (c == NULL || elem == NULL)
        return -1;

    pthread_mutex_lock(&c->mtx);

    while (c->size == 0)
        pthread_cond_wait(&c->remove, &c->mtx);

    register void* const elem_ptr = &c->buf[c->start * c->elem_size];

    memcpy(elem, elem_ptr, c->elem_size);

    c->start = channel_index(c, 1);
    --c->size;

    pthread_cond_signal(&c->add);
    pthread_mutex_unlock(&c->mtx);

    return 0;
}

Channel* channel_new(register size_t const n_elem,
                     register size_t const elem_size) {
    if (n_elem == 0 || elem_size == 0)
        return NULL;

    register size_t const channel_size = sizeof(Channel) + n_elem * elem_size;

    register Channel* const c = calloc(1, channel_size);

    if (c == NULL)
        return NULL;

    c->elem_size = elem_size;
    c->n_elem = n_elem;

    pthread_mutex_init(&c->mtx, NULL);
    pthread_cond_init(&c->add, NULL);
    pthread_cond_init(&c->remove, NULL);

    return c;
}

void channel_delete(register Channel* const c) {
    if (c == NULL)
        return;

    pthread_mutex_destroy(&c->mtx);
    pthread_cond_destroy(&c->add);
    pthread_cond_destroy(&c->remove);

    free(c);
}

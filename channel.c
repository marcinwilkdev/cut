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

inline static size_t channel_index(Channel const* const channel, size_t pos) {
    pos %= channel->n_elem;

    size_t channel_index = channel->start + pos;
    channel_index %= channel->n_elem;

    return channel_index;
}

int channel_push(register Channel* const restrict channel,
                 register void const* const restrict elem) {
    if (channel == NULL || elem == NULL)
        return -1;

    pthread_mutex_lock(&channel->mtx);

    while (channel->size == channel->n_elem)
        pthread_cond_wait(&channel->add, &channel->mtx);

    register size_t const elem_index = channel_index(channel, channel->size);
    register uint8_t* const elem_ptr = &channel->buf[elem_index * channel->elem_size];

    memcpy(elem_ptr, elem, channel->elem_size);

    ++channel->size;

    pthread_cond_signal(&channel->remove);
    pthread_mutex_unlock(&channel->mtx);

    return 0;
}

int channel_pop(register Channel* const restrict channel,
                register void* const restrict elem) {
    if (channel == NULL || elem == NULL)
        return -1;

    pthread_mutex_lock(&channel->mtx);

    while (channel->size == 0)
        pthread_cond_wait(&channel->remove, &channel->mtx);

    register void* const elem_ptr = &channel->buf[channel->start * channel->elem_size];

    memcpy(elem, elem_ptr, channel->elem_size);

    channel->start = channel_index(channel, 1);
    --channel->size;

    pthread_cond_signal(&channel->add);
    pthread_mutex_unlock(&channel->mtx);

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

void channel_delete(register Channel* const channel) {
    if (channel == NULL)
        return;

    pthread_mutex_destroy(&channel->mtx);
    pthread_cond_destroy(&channel->add);
    pthread_cond_destroy(&channel->remove);

    free(channel);
}

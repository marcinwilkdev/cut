#ifndef CHANNEL_H
#define CHANNEL_H

#include <stdbool.h>
#include <stdlib.h>

/* The channel is a generic ring buffer with thread
 * safe push and pop operations which will block the calling thread
 * until operation can be performed.*/
typedef struct Channel Channel;

/* Pushes element to the channel. If the channel is full it
 * blocks calling thread until an element was popped of the channel.
 * Returns -1 if the channel or element is NULL and 0 otherwise. */
int channel_push(Channel* __restrict c, void const* __restrict elem);
/* Pops element off the channel. If the channel is empty it
 * blocks calling thread until an element was pushed the channel.
 * Returns -1 if the channel or element is NULL and 0 otherwise. */
int channel_pop(Channel* __restrict c, void* __restrict elem);
/* Returns channel's size or 0 if channel is NULL. */
size_t channel_size(Channel* channel);

/* Creates new channel with n_elem capacity and elem_size
 * size of element in bytes. Returns NULL if memory couldn't be allocated
 * or if n_elem or elem_size equals 0. */
Channel* channel_new(size_t n_elem, size_t elem_size);
/* Safely deletes channel and deallocates memory. */
void channel_delete(Channel* c);

#endif

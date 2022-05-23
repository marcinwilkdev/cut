#ifndef CORE_UTIL_MESSAGE_H
#define CORE_UTIL_MESSAGE_H

#include <stdlib.h>
#include <stdbool.h>

/* Used for message passing between Analyzer and Reader threads. Can hold
 * message or be empty. If message is empty it indicates that program
 * has to end. */
typedef struct Core_util_message Core_util_message;

struct Core_util_message {
    size_t core_num;
    size_t util;
    bool empty;
    char padd[7];
};

/* Creates new instance of Core_util_message or returns NULL if couldn't alloc memory. */
Core_util_message* core_util_message_new(size_t core_num, size_t util);
/* Safely deletes instance of Core_util_message and deallocates memory.
 * Does nothing if core_util_message is NULL. */
void core_util_message_delete(Core_util_message* core_util_message);

/* Creates empty instance of core_util_message which indicates that
 * the program has to end. Returns NULL if couldn't allocate memory. */
Core_util_message* core_util_message_empty(void);

#endif

#ifndef TEXT_MESSAGE_H
#define TEXT_MESSAGE_H

#include <stdbool.h>
#include <stdlib.h>

/* Used for message passing between Reader and Analyzer threads. Can hold
 * message or be empty. If message is empty it indicates that program
 * has to end. */
typedef struct Text_message Text_message;

/* Creates new Text_message with text in it. Returns NULL if len is equal
 * to 0 or if couldn't malloc memory for message. */
Text_message* text_message_new(size_t len, char const text[len]);
/* Safely deletes message and deallocates memory. Does nothing if NULL passed
 * as an argument. */
void text_message_delete(Text_message* message);

/* Creates special Text_message of type empty which indicates that
 * the program has to end. Returns NULL if couldn't allocate memory for message. */
Text_message* text_message_empty(void);

/* Checks if Text_message is empty. Returns true if message is NULL. */
bool text_message_is_empty(Text_message const* message);
/* Returns text from Text_message or NULL if Text_message is NULL or empty. */
char const* text_message_message(Text_message const* message);

#endif

#ifndef LOG_MESSAGE_H
#define LOG_MESSAGE_H

#include <stdlib.h>
#include <stdbool.h>

/* Indicates from which thread comes this log_message or
 * if it is empty. Empty message tells that program has to end. */
enum log_type { reader, analyzer, printer, empty };

/* Message passed between working threads and Logger thread.
 * It has information about thread which has sent the log 
 * or is empty message which informes that program has to end. */
typedef struct Log_message Log_message;

/* Creates new Log_message instance. Return NULL if couldn't allocate
 * memory or if len equals 0. */
Log_message* log_message_new(enum log_type type, size_t len, char const text[len]);
/* Safely deletes log_message and deallocates memory. Does nothing
 * if NULL passed as an argument. */
void log_message_delete(Log_message* log_message);

/* Creates special type of Log_message called empty. */
Log_message* log_message_empty(void);

/* Returns type of log_message or empty if log_message is NULL. */
enum log_type log_message_type(Log_message const* log_message);
/* Returns text of log_message or NULL if log_message is empty or NULL. */
char const* log_message_text(Log_message const* log_message);
/* Returns true if log_message is empty or NULL. False otherwise. */
bool log_message_is_empty(Log_message const* log_message);

#endif

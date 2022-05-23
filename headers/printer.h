#ifndef PRINTER_H
#define PRINTER_H

#include "channel.h"
#include "watcher.h"

/* Worker responsible for taking message from Analyzer worker,
 * and printing them to the screen. */
typedef struct Printer Printer;

struct Printer {
    Channel* core_util_channel;
    Channel* log_channel;
    Watcher* watcher;
};

/* Starts Printer which will read core_util_messages from core_util_channel until
 * empty message encountered. Every message is printed to the screen so
 * that data can be easily analyzed. Returns if analyzer is NULL. */
void printer_start(Printer* printer);

/* Returns new instance of Printer or NULL if couldn't allocate memory. */
/* Printer* printer_new(Channel* core_util_channel, Channel* log_channel, Watcher* watcher); */
/* Safely deletes printer and deallocates memory. Does nothing if NULL passed. */
/* void printer_delete(Printer* printer); */

#endif

#ifndef READER_H
#define READER_H

#include <signal.h>
#include <stdlib.h>

#include "channel.h"
#include "watcher.h"

/* This worker is responsible for reading data from /proc/stat file
 * and sending it through channel to Analyzer worker. It's reader_start
 * method should be launched on it's own thread. It also sends logs through
 * log_channel and signals working through watcher. It will send special 
 * message to close channel when signal field signals that program should end. */
typedef struct Reader Reader;

struct Reader {
    Channel* text_channel;
    Channel* log_channel;
    Watcher* watcher;
    sig_atomic_t volatile* interrupt;
};

/* Returns new instance of Reader. */
Reader reader_new(Channel* text_channel, Channel* log_channel, Watcher* watcher,
                  sig_atomic_t volatile* interrupt);

/* After using this method Reader will read contents of /proc/stat file line
 * by line and send these chunks through text_channel until program not
 * ended by signal variable. */
void reader_start(Reader* reader);

#endif

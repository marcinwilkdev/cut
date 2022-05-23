#ifndef ANALYZER_H
#define ANALYZER_H

#include <stdlib.h>

#include "channel.h"
#include "watcher.h"

/* Worker responsible for taking message from Reader worker,
 * analyzing them (checking if contains core information and if so
 * calculating core utilization) and sending it through channel to
 * Printer worker. */
typedef struct Analyzer Analyzer;

/* Starts Analyzer which will read text_messages from text_channel until
 * empty message encountered. Every message is analyzed and if contains
 * cpu core information it calculates core utilization and sends it
 * to Reader worker. If empty message comes it sends empty core util
 * message to Printer worker and ends itself. Returns if analyzer is NULL. */
void analyzer_start(Analyzer* analyzer);

/* Returns new instance of Analyzer or NULL if couldn't allocate memory. */
Analyzer* analyzer_new(Channel* text_channel, Channel* core_util_channel, Channel* log_channel,
                       Watcher* watcher, size_t cores_count);
/* Safely deltes and deallocates instance of Analyzer. Does nothing if analyzer is NULL. */
void analyzer_delete(Analyzer* analyzer);

#endif

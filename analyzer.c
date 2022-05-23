#include <stdio.h>
#include <string.h>

#include "analyzer.h"
#include "log_message.h"
#include "text_message.h"
#include "core_util_message.h"

#define BUFF_SIZE 256

typedef struct Core_util Core_util;

struct Core_util {
    size_t idle;
    size_t total;
};

struct Analyzer {
    Channel* text_channel;
    Channel* core_util_channel;
    Channel* log_channel;
    Watcher* watcher;
    Core_util cores_prevs[];
};

inline static void
analyzer_log_discard(register Analyzer const* const analyzer) {
    char buff[BUFF_SIZE];

    register int const log_len =
        sprintf(buff, "Line doesn't contain core info. Discarding...");

    if (log_len < 0) {
        fprintf(stderr, "Couldn't create log message.");
    } else {
        Log_message* const log_message =
            log_message_new(log_analyzer, (size_t)log_len + 1, buff);

        if (log_message == NULL)
            fprintf(stderr, "Couldn't create log message.");
        else
            channel_push(analyzer->log_channel, &log_message);
    }
}

inline static void analyzer_log_core(register Analyzer const* const analyzer,
                                     register size_t const core_num) {
    char buff[BUFF_SIZE];

    register int const log_len =
        sprintf(buff, "Sending usage from core %zu...", core_num);

    if (log_len < 0) {
        fprintf(stderr, "Couldn't create log message.");
    } else {
        Log_message* const log_message =
            log_message_new(log_analyzer, (size_t)log_len + 1, buff);

        if (log_message == NULL)
            fprintf(stderr, "Couldn't create log message.");
        else
            channel_push(analyzer->log_channel, &log_message);
    }
}

static void analyzer_parse_line(register Analyzer* const analyzer,
                                register char const* const line) {
    char* line_pos = strstr(line, "cpu");

    watcher_notify(analyzer->watcher);

    if (line_pos == NULL || line_pos[3] == ' ') {
        analyzer_log_discard(analyzer);

        return;
    }

    register size_t const core_num = strtoul(&line_pos[3], &line_pos, 10);

    register size_t const user = strtoul(line_pos, &line_pos, 10);
    register size_t const nice = strtoul(line_pos, &line_pos, 10);
    register size_t const system = strtoul(line_pos, &line_pos, 10);
    register size_t const file_idle = strtoul(line_pos, &line_pos, 10);
    register size_t const iowait = strtoul(line_pos, &line_pos, 10);
    register size_t const irq = strtoul(line_pos, &line_pos, 10);
    register size_t const softirq = strtoul(line_pos, &line_pos, 10);
    register size_t const steal = strtoul(line_pos, &line_pos, 10);

    register size_t const non_idle =
        user + nice + system + irq + softirq + steal;
    register size_t const idle = file_idle + iowait;

    register size_t const total = idle + non_idle;

    Core_util const core_prev = analyzer->cores_prevs[core_num];

    if (core_prev.total != 0) {
        register size_t const totald = total - core_prev.total;
        register size_t const idled = idle - core_prev.idle;

        register size_t const percentage = 100 * (totald - idled) / totald;

        Core_util_message* const core_util_message = core_util_message_new(core_num, percentage);

        analyzer_log_core(analyzer, core_num);

        channel_push(analyzer->core_util_channel, &core_util_message);
    }

    analyzer->cores_prevs[core_num] = (Core_util){
        .total = total,
        .idle = idle,
    };
}

void analyzer_start(register Analyzer* const analyzer) {
    for (;;) {
        Text_message* line = {0};
        channel_pop(analyzer->text_channel, &line);

        if (text_message_is_empty(line)) {
            text_message_delete(line);

            Core_util_message* const core_util_message = core_util_message_empty();
            channel_push(analyzer->core_util_channel, &core_util_message);

            break;
        }

        analyzer_parse_line(analyzer, text_message_message(line));
        text_message_delete(line);
    }
}

Analyzer* analyzer_new(register Channel* const text_channel,
                       register Channel* const core_util_channel,
                       register Channel* const log_channel,
                       register Watcher* const watcher,
                       register size_t const cores_count) {
    register size_t const analyzer_size =
        sizeof(Analyzer) + sizeof(Core_util[cores_count]);

    register Analyzer* const analyzer = calloc(1, analyzer_size);

    if (analyzer == NULL)
        return NULL;

    *analyzer = (Analyzer){
        .text_channel = text_channel,
        .core_util_channel = core_util_channel,
        .log_channel = log_channel,
        .watcher = watcher,
    };

    return analyzer;
}

void analyzer_delete(register Analyzer* const analyzer) { free(analyzer); }

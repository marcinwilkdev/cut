#include <stdio.h>

#include "core_util_message.h"
#include "log_message.h"
#include "printer.h"

#define BUFF_SIZE 256

void printer_start(register Printer* const printer) {
    for (;;) {
        watcher_notify(printer->watcher);

        Core_util_message* core_util_message = {0};

        channel_pop(printer->core_util_channel, &core_util_message);

        if (core_util_message->empty) {
            core_util_message_delete(core_util_message);

            break;
        }

        if (core_util_message->core_num == 0)
            system("clear");

        char buff[BUFF_SIZE];

        register int const log_len =
            sprintf(buff, "Printing usage from core %zu...",
                    core_util_message->core_num);

        if (log_len < 0) {
            fprintf(stderr, "Couldn't create log message.");
        } else {
            Log_message* const log_message =
                log_message_new(log_printer, (size_t)log_len + 1, buff);

            if (log_message == NULL)
                fprintf(stderr, "Couldn't create log message.");
            else
                channel_push(printer->log_channel, &log_message);
        }

        printf("Core %zu: %zu%%\n", core_util_message->core_num,
               core_util_message->util);

        core_util_message_delete(core_util_message);
    }

    watcher_notify(printer->watcher);
}

add_library(${PROJECT_NAME}-lib STATIC)

target_sources(${PROJECT_NAME}-lib
    PUBLIC
        analyzer.h
        channel.h
        core_util_message.h
        helper.h
        logger.h
        log_message.h
        printer.h
        reader.h
        text_message.h
        watchdog.h
        watcher.h
    PRIVATE
        analyzer.c
        channel.c
        core_util_message.c
        helper.c
        logger.c
        log_message.c
        printer.c
        reader.c
        text_message.c
        watchdog.c
        watcher.c
    )

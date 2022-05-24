add_executable(channel_test channel_test.c)
target_link_libraries(channel_test PUBLIC ${PROJECT_NAME}-lib)

add_executable(analyzer_test analyzer_test.c)
target_link_libraries(analyzer_test PUBLIC ${PROJECT_NAME}-lib)

add_executable(core_util_message_test core_util_message_test.c)
target_link_libraries(core_util_message_test PUBLIC ${PROJECT_NAME}-lib)

add_executable(helper_test helper_test.c)
target_link_libraries(helper_test PUBLIC ${PROJECT_NAME}-lib)

add_executable(log_message_test log_message_test.c)
target_link_libraries(log_message_test PUBLIC ${PROJECT_NAME}-lib)

add_executable(logger_test logger_test.c)
target_link_libraries(logger_test PUBLIC ${PROJECT_NAME}-lib)

add_executable(printer_test printer_test.c)
target_link_libraries(printer_test PUBLIC ${PROJECT_NAME}-lib)

add_executable(reader_test reader_test.c)
target_link_libraries(reader_test PUBLIC ${PROJECT_NAME}-lib)

add_executable(text_message_test text_message_test.c)
target_link_libraries(text_message_test PUBLIC ${PROJECT_NAME}-lib)

add_executable(watcher_test watcher_test.c)
target_link_libraries(watcher_test PUBLIC ${PROJECT_NAME}-lib)

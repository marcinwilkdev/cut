cmake_minimum_required(VERSION 3.14)

project(cut LANGUAGES C)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_C_FLAGS_DEBUG "-O0 -ggdb3")
set(CMAKE_C_FLAGS_RELEASE "-O3 -march=native")

if(CMAKE_C_COMPILER_ID MATCHES GNU)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
endif()

if(CMAKE_C_COMPILER_ID MATCHES Clang)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Weverything -Wno-vla -Wno-declaration-after-statement")
endif()

add_subdirectory(src)
add_subdirectory(test_src)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}-lib)

enable_testing()

add_test(
    NAME channel_test
    COMMAND channel_test
    )

add_test(
    NAME core_util_message_test
    COMMAND core_util_message_test
    )

add_test(
    NAME helper_test
    COMMAND helper_test
    )

add_test(
    NAME log_message_test
    COMMAND log_message_test
    )

add_test(
    NAME text_message_test
    COMMAND text_message_test
    )

add_test(
    NAME analyzer_test
    COMMAND analyzer_test
    )

add_test(
    NAME logger_test
    COMMAND logger_test
    )

add_test(
    NAME printer_test
    COMMAND printer_test
    )

add_test(
    NAME reader_test
    COMMAND reader_test
    )

add_test(
    NAME watcher_test
    COMMAND watcher_test
    )

cmake_minimum_required(VERSION 3.5)

# === Build type (default: RelWithDebInfo, O2) ===========
if (NOT CMAKE_BUILD_TYPE)
    set(BUILD_TYPE_OPTIONS
        "Choose the type of build, "
        "options are: Debug Release RelWithDebInfo MinSizeRel.")
    set(CMAKE_BUILD_TYPE "RelWithDebInfo"
        CACHE ${BUILD_TYPE_OPTIONS} FORCE)
    message(STATUS "Build type is not given, use default.")
endif ()
message(STATUS "Build type: " ${CMAKE_BUILD_TYPE})


set(ROOT_SRC ${PROJECT_SOURCE_DIR}/src)
set(EXAMPLE_DIR ${PROJECT_SOURCE_DIR}/examples)

set(LIBDL dl)

# Includes
include_directories(BEFORE ./)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/src)

# Compiler flags
if (NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    if (NOT APPLE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    endif ()
endif()

if (ADDRESS_SANITIZER GREATER 0)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold")
    message(STATUS "---- ADDRESS SANITIZER IS ON ----")
endif()

if (THREAD_SANITIZER GREATER 0)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold")
    add_definitions(-DSUPPRESS_TSAN_FALSE_ALARMS=1)
    message(STATUS "---- THREAD SANITIZER IS ON ----")
endif()

if (LEAK_SANITIZER GREATER 0)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
    message(STATUS "---- LEAK SANITIZER IS ON ----")
endif()


if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd5045 /wd4571 /wd4774 /wd4820 /wd5039 /wd4626 /wd4625 /wd5026 /wd5027 /wd4623 /wd4996 /W3")
    message(STATUS "---- WIN32 ----")
endif()


# === Program flags ===

if ( (TESTSUITE_NO_COLOR GREATER 0) OR (WIN32) )
    add_definitions(-DTESTSUITE_NO_COLOR=1)
    add_definitions(-DLOGGER_NO_COLOR=1)
    message(STATUS "---- NO ANSI COLOR ----")
endif()



# === Example ===

set(BASIC_TEST ${EXAMPLE_DIR}/basic_test.cc)
add_executable(basic_test ${BASIC_TEST})

set(RANGE_TEST ${EXAMPLE_DIR}/range_test.cc)
add_executable(range_test ${RANGE_TEST})

set(MULTI_ARGS_TEST ${EXAMPLE_DIR}/multi_args_test.cc)
add_executable(multi_args_test ${MULTI_ARGS_TEST})

set(CLI_ARGS_TEST ${EXAMPLE_DIR}/cli_args_test.cc)
add_executable(cli_args_test ${CLI_ARGS_TEST})

set(MESSAGE_TEST ${EXAMPLE_DIR}/message_test.cc)
add_executable(message_test ${MESSAGE_TEST})

set(THREAD_TEST ${EXAMPLE_DIR}/thread_test.cc)
add_executable(thread_test ${THREAD_TEST})

set(PROGRESS_TEST ${EXAMPLE_DIR}/progress_test.cc)
add_executable(progress_test ${PROGRESS_TEST})

set(VERIFY_MULTI_INCLUDE
    ${EXAMPLE_DIR}/verify_multi_include.cc
    ${EXAMPLE_DIR}/dummy.cc)
add_executable(verify_multi_include ${VERIFY_MULTI_INCLUDE})


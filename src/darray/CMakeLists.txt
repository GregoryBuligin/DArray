cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

find_package(Threads REQUIRED)

set(LIB_SOURCES
    src/darray.c
)

set(MAIN_SOURCES
    src/main.c
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Werror")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/darray)

add_library(darray SHARED ${LIB_SOURCES})

add_executable(main ${MAIN_SOURCES})
target_link_libraries(main darray Threads::Threads)

# Subdirectories
add_subdirectory(tests)

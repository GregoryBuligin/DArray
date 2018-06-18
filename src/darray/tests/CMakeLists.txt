cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include/darray)

enable_testing()

# Packages
find_package(Threads REQUIRED)
find_package(Check REQUIRED)

include_directories(${CHECK_INCLUDE_DIRS})

# Libs
set(LIBS ${LIBS} ${CHECK_LIBRARIES} darray)

# Executable with link
add_executable(test_darray test_darray.c)
target_link_libraries(test_darray ${LIBS} Threads::Threads)

# Tests path
add_test(test_darray ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_darray)

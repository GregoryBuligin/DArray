cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(dynamic_array LANGUAGES C)

# enable C11 standard
set(CMAKE_C_STANDARD 11)

# Set build features
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")

set(THREADS_PREFER_PTHREAD_FLAG ON)

include(GNUInstallDirs)
include(CheckCSourceCompiles)
include(CheckCSourceRuns)
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(CheckSymbolExists)
include(CheckTypeSize)
include(CTest)

enable_testing()

# find_package(Check REQUIRED)

# Subdirectories
add_subdirectory(src)
# add_subdirectory(tests)

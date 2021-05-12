cmake_minimum_required(VERSION 2.8)
project(file_proc)
set(SOURCES
    file_proc.cpp
    )
add_library(file_proc_lib ${SOURCES})
target_include_directories(file_proc_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..) # /src


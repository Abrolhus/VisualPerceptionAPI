cmake_minimum_required(VERSION 2.8)
project(file_proc)
set(SOURCES
    file_proc.cpp
    )
set(FILE_PROC_LIB file_proc_lib PARENT_SCOPE)
add_library(file_proc_lib ${SOURCES})


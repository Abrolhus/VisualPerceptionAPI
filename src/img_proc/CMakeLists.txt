cmake_minimum_required(VERSION 2.8)
project(img_proc)
set(SOURCES
    img_proc.cpp
    )
add_library(img_proc_lib ${SOURCES})
target_include_directories(img_proc_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..) # /src


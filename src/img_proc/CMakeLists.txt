cmake_minimum_required(VERSION 2.8)
project(img_proc)
set(SOURCES
    img_proc.cpp
    )
set(IMG_PROC_LIB img_proc_lib PARENT_SCOPE)
add_library(img_proc_lib ${SOURCES})


cmake_minimum_required(VERSION 2.8)
project(field_color_detection)
set(SOURCES
    field_color_detector.cpp
    )
add_library(field_color_detection_lib ${SOURCES})
target_include_directories(field_color_detection_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..) # /src


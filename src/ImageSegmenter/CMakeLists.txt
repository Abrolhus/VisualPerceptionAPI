cmake_minimum_required(VERSION 2.8)
project(image_segmenter)
set(SOURCES
        ImageSegmenter.cpp
        ImageRegion.cpp
    )
set(IMAGE_SEGMENTER_LIB ImageSegmenter_lib PARENT_SCOPE)
add_library(ImageSegmenter_lib  ${SOURCES})


cmake_minimum_required(VERSION 2.8)
project(image_segmenter)
set(SOURCES
        Image_Segmenter.cpp
        Image_Region.cpp
    )
set(IMAGE_SEGMENTER_LIB ImageSegmenter_lib PARENT_SCOPE)
add_library(ImageSegmenter_lib  ${SOURCES})

